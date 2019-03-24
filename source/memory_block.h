#pragma once
#include <cstdint>

namespace mcpgnz
{
    /* represents chunk of memory */
    struct memory_block
    {
        #pragma region variables
        uint8_t* _address = nullptr;
        uint32_t _bytes = 0;
        #pragma endregion

        #pragma region methods
        memory_block(void) = default;
        memory_block(void* address, uint32_t bytes);

        /* does the memory_block points to valid memory block*/
        bool is_valid() const;

        /* does the memory_block contains given address */
        bool contains(const void* address) const;
        #pragma endregion
    };
}
