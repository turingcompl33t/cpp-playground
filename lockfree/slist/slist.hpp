// slist.hpp
// A simple lock-free implementation of a singly-linked list data structure.

#include <atomic>
#include <memory>
#include <utility>

template <typename T>
class slist
{
    struct node
    {
        T                     data_;
        std::shared_ptr<node> next_;
    };

    class reference
    {
        std::shared_ptr<node> p_;

    public:
        reference(std::shared_ptr<node> p)
            : p_{ p }
        {}
        T& operator*() { return p_->data_; }
        T* operator->() { return &p->data_; }
    };

    std::shared_ptr<node> head_{ nullptr };

public:
    slist()  = default;
    ~slist() = default;

    auto find(T data) const
    {
        auto p = std::atomic_load(&head_);
        while (p && p->data_ != data)
        {
            p = p->next_;
        }
        return reference(std::move(p));
    }

    void push_front(T data)
    {
        auto p = std::make_shared<node>();
        p->data_ = data;
        p->next_ = head_;
        
        // try to swap until successful
        while (!std::atomic_compare_exchange_weak(&head_, &p->next_, p)) {}
    }

    void pop_front()
    {
        auto p = std::atomic_load(&head_);

        // try to swap until successful
        while (p && !std::atomic_compare_exchange_weak(&head_, &p, p->next_)) {}
    }
};