#pragma once
#include "memory_block.h"
#include "allocator.h"

namespace mcpgnz
{
    /* uses malloc to provide requested memory */
    struct malloc_allocator : allocator
    {
        #pragma region methods
        memory_block allocate(uint32_t bytes) final override;
        void deallocate(const memory_block&) final override;

        /* [note] asserts that it owns all memory_blocks*/
        bool owns(const memory_block&) const final override;
        #pragma endregion
    };
}
