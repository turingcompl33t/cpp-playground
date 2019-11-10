// UniquePtr.cpp
// A simple implementation of std::unqiue_ptr.

#include <iostream>

template<typename T>
class UniquePtr
{
public:
    UniquePtr() = default;
    UniquePtr(T *p) 
        : m_ptr{ p } 
    {
        std::cout << "[UniquePtr]: Constructed" << std::endl;
    }
    
    ~UniquePtr()
    {
        if (m_ptr)
        {
            delete m_ptr;
        }
        
        std::cout << "[UniquePtr]: Destructed" << std::endl;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other)
        : m_ptr { other.m_ptr }
    {
        other.m_ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other)
    {
        if (m_ptr)
        {
            delete m_ptr;
        }

        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;

        return *this;
    }

    T operator*()
    {
        return *m_ptr;
    }

    operator bool() const
    {
        return m_ptr != nullptr;
    }

    T* get() const
    {
        return m_ptr;
    }

private:
    T* m_ptr;
};

template<typename T, typename... Args>
UniquePtr<T> MakeUnique(Args... args)
{
    return UniquePtr<T>{ new T{ args... } };
}

int main()
{
    auto outer = MakeUnique<int>(10);

    {
        auto ptr = MakeUnique<int>(5);
    }
}