#include "malloc_allocator.h"
#include <cstdlib>

namespace mcpgnz
{
    #pragma region public methods
    memory_block malloc_allocator::allocate(const uint32_t bytes)
    {
        return memory_block
        {
            malloc(bytes),
            bytes
        };
    }

    void malloc_allocator::deallocate(const memory_block& memory_block)
    {
        free(memory_block._address);
    }

    bool malloc_allocator::owns(const memory_block&) const
    {
        return true;
    }
    #pragma endregion
}