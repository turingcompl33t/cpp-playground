// list.cpp
// Messing with list and a custom allocator.

#include <list>
#include <cstdio>
#include <cstdlib>
#include <iostream>

template <typename T>
class FreeListAllocator
{
    struct Header
    {
        Header*     next;
        std::size_t size;
    };

    Header* root;

public:
    using size_type             = std::size_t;
    using difference_type       = std::ptrdiff_t;
    using pointer_type          = T*;
    using const_pointer_type    = const T*;
    using reference_type        = T&;
    using const_reference_type  = const T&;
    using value_type            = T;

    FreeListAllocator() : root{nullptr} {}
    
    ~FreeListAllocator()
    {
        auto* current = root;
        while (current != nullptr)
        {
            auto* next = current->next;
            ::free(current);
            current = next;
        }
    }

    pointer_type allocate(size_type n)
    {
        const auto request_size = n*sizeof(value_type);

        printf("[ALLOC] items: %lu (request size: %lu)\n", n, request_size);

        if (root != nullptr && root->size <= request_size)
        {
            auto* entry = root;
            root = root->next;

            printf("\tServicing from free list; provided size: %lu\n", entry->size);

            return reinterpret_cast<pointer_type>(
                reinterpret_cast<char*>(entry) + sizeof(Header));
        }

        printf("\tServicing with backing allocator; allocating: %lu\n", sizeof(Header) + request_size);

        auto* ptr = ::malloc(sizeof(Header) + request_size);
        if (nullptr == ptr)
        {
            throw std::bad_alloc{};
        }

        return reinterpret_cast<pointer_type>(
            static_cast<char*>(ptr) + sizeof(Header));
    }

    void deallocate(pointer_type ptr, size_type n)
    {
        const auto freed_size = n*sizeof(value_type);

        printf("[FREE] items: %lu (freed size: %lu)\n", n, freed_size);

        auto new_entry = reinterpret_cast<Header*>(
            reinterpret_cast<char*>(ptr) - sizeof(Header));
        new_entry->size = freed_size;
        new_entry->next = root;
        root = new_entry;
    }
};

int main()
{
    std::list<int, FreeListAllocator<int>> l{};

    l.push_back(1);
    l.push_back(2);

    l.pop_back();

    l.push_back(4);

    return EXIT_SUCCESS;
}