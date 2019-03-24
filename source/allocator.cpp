#include "allocator.h"
#include <cstdio>

namespace mcpgnz
{
    #pragma region public variables
    /* provide default error callback*/
    void(*allocator::_error_callback)(const char[]) = [](const char* message)
    {
        printf(message);
    };
    #pragma endregion

    #pragma region public methods
    bool allocator::expand(memory_block&, const uint32_t bytes)
    {
        /* by default - do not support expanding */
        return false;
    }
    #pragma endregion
}