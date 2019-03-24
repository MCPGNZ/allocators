#pragma once
#include "memory_block.h"
#include "allocator.h"

namespace mcpgnz
{
    /*  defines an allocator that uses <Main> allocator as long as it can handle the memory requests,
        uses <Fallback> otherwise (if the <Main> is unable to allocate requested memory) */
    template <typename Main, typename Fallback>
    class fallback_allocator : public allocator
    {
    public:
        #pragma region methods
        memory_block allocate(uint32_t bytes) final override;
        void deallocate(const memory_block& block) final override;

        bool owns(const memory_block& block) const final override;
        #pragma endregion

    private:
        #pragma region variables
        Main _main;
        Fallback _fallback;
        #pragma endregion
    };

    #pragma region template implementation
    template <typename Main, typename Fallback>
    memory_block fallback_allocator<Main, Fallback>::allocate(const uint32_t bytes)
    {
        auto result = _main.allocate(bytes);
        if (result.is_valid())
        {
            return result;
        }

        return _fallback.allocate(bytes);
    }

    template <typename Main, typename Fallback>
    void fallback_allocator<Main, Fallback>::deallocate(const memory_block& block)
    {
        if (_main.owns(block))
        {
            _main.deallocate(block);
            return;
        }

        _fallback.deallocate(block);
    }

    template <typename Main, typename Fallback>
    bool fallback_allocator<Main, Fallback>::owns(const memory_block& block) const
    {
        return _main.owns(block) || _fallback.owns(block);
    }
    #pragma endregion
}
