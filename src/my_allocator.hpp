#pragma once
#include <array>
#include <cstddef>
#include <iostream>

template <typename T>
struct my_allocator;

template <typename V>
struct my_allocator<std::pair<const size_t, V>> {
    using value_type = std::pair<const size_t, V>;
    using pointer = std::pair<const size_t, V>*;
    using const_pointer = const std::pair<const size_t, V>*;
    using reference = std::pair<const size_t, V>&;
    using const_reference = const std::pair<const size_t, V>&;

    template <typename U>
    struct rebind {
        using other = my_allocator<U>;
    };

    my_allocator() = default;
    ~my_allocator() = default;

    // Не хочу копировать мапу
    template <typename U, size_t M>
    my_allocator(const my_allocator<U>&) = delete;

    pointer* allocate(std::size_t n) {
        std::cout << "allocate" << std::endl;
        return alloc.allocate(n);
    }
    void deallocate(pointer* p, std::size_t n) {
        std::cout << "deallocate" << std::endl;
        alloc.deallocate(p, n);
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        std::cout << "construct" << std::endl;
        // new (p) U(std::forward<Args>(args)...);
    };

    template <typename U>
    void destroy(U* p) {
        std::cout << "destroy" << std::endl;
        // p->~U();
    }

   private:
    typename std::allocator<value_type> alloc{};
    // typename std::array<T, MAX> _stor{};
    // typename std::array<T, MAX>::iterator _begin = _stor.begin();
};
