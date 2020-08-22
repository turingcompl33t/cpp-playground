// stack.hpp
// A minimal lock-free implementation of a thread-safe stack data structure.

#pragma once

#include <memory>
#include <atomic>

// stack
//
// Lock-free stack implementation utilizing manual
// reference counting to manage node leaks.

template <typename T>
class stack
{
private:
    struct node
    {
        std::shared_ptr<T> data_;
        node* next_;
        node(T const& data) 
            : data_{std::make_shared<T>(data)}
        {}
    };

    std::atomic<node*>    head_;
    std::atomic<unsigned> threads_in_pop_;
    std::atomic<node*>    to_be_deleted_;

public:
    void push(T const& data)
    {
        node* const new_node = new node(data);
        new_node->next_ = head_.load();
        while (!head_.compare_exchange_weak(new_node->next_, new_node));
    }

    std::shared_ptr<T> pop()
    {
        ++threads_in_pop_;
        node* popped_node = head_.load();
        while (popped_node &&
            !head_.compare_exchange_weak(popped_node, popped_node->next_));
        
        std::shared_ptr<T> res{};
        if (popped_node)
        {
            res.swap(popped_node->data_);
        }
        try_reclaim(popped_node);
        return res;
    }

private:
    void try_reclaim(node* popped_node)
    {
        if (1 == threads_in_pop_)
        {
            node* nodes_to_delete = to_be_deleted_.exchange(nullptr);
            if (!--threads_in_pop_)
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
            chain_pending_nodes(popped_node);
            --threads_in_pop_;
        }
    }

    void chain_pending_nodes(node* nodes)
    {
        node* last = nodes;
        while (node* const next = last->next_)
        {
            last = next;
        }

        chain_pending_nodes(nodes, last);
    }

    void chain_pending_nodes(node* first, node* last)
    {
        last->next_ = to_be_deleted_;
        while (!to_be_deleted_.compare_exchange_weak(last->next_, first));
    }

    void chain_pending_node(node* n)
    {
        chain_pending_nodes(n, n);
    }

    static void delete_nodes(node* nodes)
    {
        while (nodes)
        {
            node* next = nodes->next_;
            delete nodes;
            nodes = next;
        }
    }
};