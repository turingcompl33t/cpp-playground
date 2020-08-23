// stack.hpp
//
// A lock-free stack implementation utilizing an explicit counter
// of the number of threads active in the critical section of the
// code to detect when it is safe to delete popped nodes.
//
// This stack relies on the existence of quiscent states in order
// to reclaim nodes. For this reason, the approach works reasonably
// well in low-contention scenarios in which threads calling pop() 
// often (enough) encounter the case wherein they are the only thread
// invoking pop() at that time, allowing them to perform a reclamation
// of defferred nodes. However, under high contention, such a quiscent
// state may never actually occur, and the implicit stack of deferred
// nodes awaiting deletion may grow without bound. 
//
// Once interesting thing to note about this approach, however, is that
// it outperforms the hazard pointer-based reclamation scheme in a simple
// ping-pong benchmark by a significant margin. Thus, while this approach
// is still relatively heavy-handed and high-overhead, the overhead of 
// each attempted reclamation under zero contention is still lower than 
// that of the naive hazard pointer implementation which has to scan the
// entire array of hazard pointers on each and every pop() operation.
//
// Adapted from the example by Anthony Williams in "C++ Concurrency in Action"

#ifndef STACK_HPP
#define STACK_HPP

#include <memory>
#include <atomic>

template <typename T>
class stack
{
private:
    struct node
    {
        node*              next;
        std::shared_ptr<T> data;
        node(T const& data_) 
            : data{std::make_shared<T>(data_)}
        {}
    };

    std::atomic<node*>       head;
    std::atomic<std::size_t> threads_in_pop;
    std::atomic<node*>       to_be_deleted;

public:
    stack() 
        : head{nullptr}
        , threads_in_pop{0}
        , to_be_deleted{nullptr} {}

    ~stack() = default;

    stack(stack const&)            = delete;
    stack& operator=(stack const&) = delete;

    stack(stack&&)            = delete;
    stack& operator=(stack&&) = delete;

    void push(T const& data)
    {
        node* const new_node = new node{data};
        new_node->next = head.load();
        while (!head.compare_exchange_weak(new_node->next, new_node));
    }

    std::shared_ptr<T> pop()
    {
        ++threads_in_pop;
        node* popped_node = head.load();
        while (popped_node &&
            !head.compare_exchange_weak(popped_node, popped_node->next));
        
        std::shared_ptr<T> popped{};
        if (popped_node)
        {
            popped.swap(popped_node->data);
        }

        try_reclaim(popped_node);
        return popped;
    }

    bool is_empty_unsafe() const noexcept
    {
        return (nullptr == head.load());
    }

private:
    void try_reclaim(node* popped_node)
    {
        if (1 == threads_in_pop.load())
        {
            node* nodes_to_delete = to_be_deleted.exchange(nullptr);
            if (0 == threads_in_pop.fetch_sub(1))
            {
                delete_nodes(nodes_to_delete);
            }
            else if (nodes_to_delete)
            {
                chain_pending_nodes(nodes_to_delete);
            }
            
            delete popped_node;
        }
        else
        {
            chain_pending_node(popped_node);
            threads_in_pop.fetch_sub(1);
        }
    }

    static void delete_nodes(node* pending_head)
    {
        while (pending_head)
        {
            node* next = pending_head->next;
            delete pending_head;
            pending_head = next;
        }
    }

    void chain_pending_nodes(node* first)
    {
        node* last = first;
        while (last->next != nullptr)
        {
            last = last->next;
        }

        chain_pending_nodes(first, last);
    }

    void chain_pending_nodes(node* first, node* last)
    {
        last->next = to_be_deleted;
        while (!to_be_deleted.compare_exchange_weak(last->next, first));
    }

    void chain_pending_node(node* n)
    {
        chain_pending_nodes(n, n);
    }
};

#endif // STACK_HPP