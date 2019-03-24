#include "memory_block.h"

namespace mcpgnz
{
    #pragma region public methods
    memory_block::memory_block(void* address, const uint32_t bytes)
        : _address{ (uint8_t*)address }, _bytes{ bytes }
    {
    }

    bool memory_block::is_valid() const
    {
        return (_address != nullptr) && (_bytes != 0);
    }

    bool memory_block::contains(const void* address) const
    {
        return (address >= _address) && (address <= ((uint8_t*)_address + _bytes - 1));
    }
    #pragma endregion
}