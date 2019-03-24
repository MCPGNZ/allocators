#pragma once
#include <cstdint>

namespace mcpgnz
{
    #pragma region forward declarations
    struct memory_block;
    #pragma endregion

    struct allocator
    {
        #pragma region variables
        static void(*_error_callback)(const char[]);
        #pragma endregion

        #pragma region methods
        allocator(void) = default;
        virtual ~allocator() = default;

        allocator(const allocator&) = default;
        allocator& operator=(const allocator&) = default;

        allocator(allocator&&) = default;
        allocator& operator=(allocator&&) = default;

        virtual memory_block allocate(uint32_t bytes) = 0;
        virtual void deallocate(const memory_block&) = 0;

        /*  is the memory_block owned by this allocator */
        virtual bool owns(const memory_block&) const = 0;

        /*  tries to allocate memory at the end of memory_block
            bytes: all bytes needed, including already allocated ones */
        virtual bool expand(memory_block&, uint32_t bytes);
        #pragma endregion
    };
}
