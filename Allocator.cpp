
#include "Allocator.h"

Allocator::Allocator(size_t size, void* start)
{
    _start = start;
    _size = size;
    _used_memory = 0;
    _num_allocations = 0;
}

Allocator::~Allocator()
{
    _start = nullptr;
    _size = 0;
}

void* Allocator::start() const noexcept
{
    return _start;
}

size_t Allocator::size() const noexcept
{
    return _size;
}

size_t Allocator::usedMemory() const noexcept
{
    return _used_memory;
}

size_t Allocator::numAllocations() const noexcept
{
    return _num_allocations;
}
