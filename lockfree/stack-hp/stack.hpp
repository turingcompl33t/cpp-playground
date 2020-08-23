// stack.hpp
//
// A lockfree stack implementation that utilizes hazard pointers
// to manage reclamation of nodes after they have been popped.
//
// Adapted from the example by Anthony Williams in "C++ Concurrency in Action"

#ifndef STACK_HPP
#define STACK_HPP

#include <memory>
#include <atomic>

#include "hazard_pointer.hpp"

template <typename T>
class stack
{
private:
    struct node
    {        
        node*              next;
        std::shared_ptr<T> data;
        node(T const& data_) 
            : next{nullptr}
            , data{std::make_shared<T>(data_)} {}
    };

    std::atomic<node*> head;

public:
    stack() : head{nullptr} {}

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
        std::atomic<void*>& hp = hazard_pointer_for_this_thread();
        node* old_head = head.load();
        do
        {
            // set our hazard pointer to the current top of the stack
            // to express the fact that we are referencing this node
            node* tmp{};
            do 
            {
                tmp = old_head;
                hp.store(old_head);
                old_head = head.load();
            } while (old_head != tmp);

        } while (old_head 
              && !head.compare_exchange_strong(old_head, old_head->next));

        // release the hazard pointer to express the fact that
        // we have successfully claimed this node for ourself
        hp.store(nullptr);

        std::shared_ptr<T> popped{};
        if (old_head)
        {
            popped.swap(old_head->data);
            if (outstanding_hazard_pointers_for(old_head))
            {
                reclaim_later(old_head);
            }
            else
            {
                delete old_head;
            }

            attempt_reclamation();
        }

        return popped;
    }

    bool is_empty_unsafe() const noexcept
    {
        return (head.load() == nullptr);
    }
};

#endif // STACK_HPP