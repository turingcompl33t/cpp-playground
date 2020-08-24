// spsc_queue.hpp
//
// A simple single-producer, single-consumer lock-free queue.

#ifndef SPSC_QUEUE_HPP
#define SPSC_QUEUE_HPP

#include <atomic>
#include <memory>

template <typename T>
class spsc_queue
{
    struct node
    {
        node*              next;
        std::shared_ptr<T> data; 

        node() : next{nullptr} {}
    };

    std::atomic<node*> head;
    std::atomic<node*> tail;

public:
    spsc_queue()
        : head{new node{}}
        , tail{head.load(std::memory_order_relaxed)}
    {}

    ~spsc_queue()
    {
        while (auto* current = head.load())
        {
            head.store(current->next);
            delete current;
        }
    }

    // non-copyable
    spsc_queue(spsc_queue const&)            = delete;
    spsc_queue& operator=(spsc_queue const&) = delete;

    // non-movable
    spsc_queue(spsc_queue&&)            = delete;
    spsc_queue& operator=(spsc_queue&&) = delete;

    void push(T const& data)
    {
        auto shared_data = std::make_shared<T>(data);

        // allocate the new "dummy" tail node
        node* new_node = new node{};

        // replace the data in the current tail node
        node* const old_tail = tail.load();
        old_tail->data.swap(shared_data);
        old_tail->next = new_node;

        // update the tail pointer
        tail.store(new_node);
    }

    std::shared_ptr<T> pop()
    {
        auto* old_head = pop_head();
        if (nullptr == old_head)
        {
            // queue is empty
            return std::shared_ptr<T>{};
        }

        std::shared_ptr<T> popped{old_head->data};
        delete old_head;

        return popped;
    }

    bool is_empty_unsafe() const noexcept
    {
        return (head.load(std::memory_order_relaxed) 
            == tail.load(std::memory_order_relaxed));
    }

private:
    // pop the current head and advance the head pointer
    node* pop_head()
    {
        node* const old_head = head.load();
        if (old_head == tail.load())
        {
            // queue is empty
            return nullptr;
        }
        head.store(old_head->next);
        return old_head;
    }
};

#endif // SPSC_QUEUE_HPP