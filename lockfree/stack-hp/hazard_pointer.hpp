// hazard_pointer.hpp
//
// Machinery for hazard pointer-based reclamation in lockfree stack.
// 
// Adapted from the example by Anthony Williams in "C++ Concurrency in Action"

#ifndef HAZARD_POINTER_HPP
#define HAZARD_POINTER_HPP

#include <atomic>
#include <thread>
#include <stdexcept>
#include <functional>

constexpr static auto const MAX_HAZARD_PTRS = 32ul;

struct hazard_pointer
{
    std::atomic<std::thread::id> id;
    std::atomic<void*>           ptr;
};

// global array of hazard pointers
hazard_pointer hazard_pointers[MAX_HAZARD_PTRS];

class hp_owner
{
    hazard_pointer* hp;

public:
    hp_owner() : hp{nullptr}
    {
        // attempt to claim a hazard pointer for this thread
        for (auto i = 0ul; i < MAX_HAZARD_PTRS; ++i)
        {
            std::thread::id null_id{};
            if (hazard_pointers[i].id.compare_exchange_strong(null_id, std::this_thread::get_id()))
            {
                // found a free hazard pointer
                hp = &hazard_pointers[i];
                break;
            }
        }

        if (!hp)
        {
            throw std::runtime_error{"no available hazard pointers"};
        }
    }

    ~hp_owner()
    {
        // release the hazard pointer slot used by this thread
        hp->ptr.store(nullptr);
        hp->id.store(std::thread::id{});
    }
    
    // non-copyable
    hp_owner(hp_owner const&)            = delete;
    hp_owner& operator=(hp_owner const&) = delete;

    // non-movable
    hp_owner(hp_owner&&)            = delete;
    hp_owner& operator=(hp_owner&&) = delete;

    std::atomic<void*>& get_pointer()
    {
        return hp->ptr;
    }
};

std::atomic<void*>& hazard_pointer_for_this_thread()
{
    static thread_local hp_owner owner{};
    return owner.get_pointer();
}

// scan the global array of hazard pointers to determine if there 
// are any outstanding hazard pointers for the specified pointer
bool outstanding_hazard_pointers_for(void* ptr)
{
    for (auto i = 0ul; i < MAX_HAZARD_PTRS; ++i)
    {
        if (hazard_pointers[i].ptr.load() == ptr)
        {
            return true;
        }
    }

    return false;
}

template <typename T>
void do_delete(void* ptr)
{
    delete static_cast<T*>(ptr);
}

struct data_to_reclaim
{
    void* ptr;
    std::function<void(void*)> deleter;
    data_to_reclaim* next;

    template <typename T>
    data_to_reclaim(T* ptr_)
        : ptr{ptr_}
        , deleter{&do_delete<T>}
        , next{nullptr} {}

    ~data_to_reclaim()
    {
        deleter(ptr);
    }
};

std::atomic<data_to_reclaim*> nodes_to_reclaim{};

void add_to_reclaim_list(data_to_reclaim* node)
{
    node->next = nodes_to_reclaim.load();
    while (!nodes_to_reclaim.compare_exchange_weak(node->next, node));
}

template <typename T>
void reclaim_later(T* data)
{
    add_to_reclaim_list(new data_to_reclaim{data});
}

// reclaim nodes with no outstanding hazards
void attempt_reclamation()
{
    data_to_reclaim* current = nodes_to_reclaim.exchange(nullptr);
    while (current != nullptr)
    {
        data_to_reclaim *const next = current->next;
        if (!outstanding_hazard_pointers_for(current->ptr))
        {
            delete current;
        }
        else
        {
            add_to_reclaim_list(current);
        }

        current = next;
    }
}

#endif // HAZARD_POINTER_HPP