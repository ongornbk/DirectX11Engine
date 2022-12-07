#pragma once
#include "gdef.h"

#include <modern__.h>

class Allocator
{
public:

    Allocator(size_t size, void* start);

    virtual ~Allocator();

    virtual void* allocate(size_t size, uint8 alignment = 4) = 0;
    virtual void deallocate(void* p) = 0;
    void* start() const modern_except_state;
    size_t size() const modern_except_state;
    size_t usedMemory() const modern_except_state;
    size_t numAllocations() const modern_except_state;

protected:

    void* _start;
    size_t _size;
    size_t _used_memory;
    size_t _num_allocations;
};

namespace allocator
{
    template <class T>
    T* allocateNew(class Allocator& allocator)
    {
        return new (allocator.allocate(sizeof(T), __alignof(T))) T;
    }

    template <class T>
    T* allocateNew(class Allocator& allocator, const T& t)
    {
        return new (allocator.allocate(sizeof(T), __alignof(T))) T(t);
    }

    template <class T>
    void deallocateDelete(class Allocator& allocator, T& object)
    {
        object.~T();
        allocator.deallocate(&object);
    }

    template <class T>
    T* allocateArray(class Allocator& allocator, size_t length)
    {
        const uint8 headerSize = sizeof(size_t) / sizeof(T);

        if (sizeof(size_t) % sizeof(T) > 0u) headerSize += 1u;

        //Allocate extra space to store array length in the bytes before the array 
        T* p = ((T*)allocator.allocate(sizeof(T) * (length + headerSize), __alignof(T))) + headerSize;
        *(((size_t*)p) - 1) = length;

        for (size_t i = 0u; i < length; i++)
            new (&p) T;

        return p;
    }

    template <class T> 
    void deallocateArray(class Allocator& allocator, T* array)
    {
        ASSERT(array != nullptr);
        size_t length = *(((size_t*)array) - 1);

        for (size_t i = 0u; i < length; i++) array.~T();

        //Calculate how much extra memory was allocated to store the length before the array 
        u8 headerSize = sizeof(size_t) / sizeof(T);
        if (sizeof(size_t) % sizeof(T) > 0u)
            headerSize += 1u;
        allocator.deallocate(array - headerSize);
    }
};