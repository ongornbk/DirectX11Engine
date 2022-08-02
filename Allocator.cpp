
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

void* Allocator::start() const modern_except_state
{
    return _start;
}

size_t Allocator::size() const modern_except_state
{
    return _size;
}

size_t Allocator::usedMemory() const modern_except_state
{
    return _used_memory;
}

size_t Allocator::numAllocations() const modern_except_state
{
    return _num_allocations;
}
