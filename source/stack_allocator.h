#pragma once
#include "memory_block.h"
#include "allocator.h"

namespace mcpgnz
{
    /* uses stack to allocate requested memory */
    template <uint32_t Size>
    class stack_allocator : public allocator
    {
    public:
        #pragma region methods
        stack_allocator(void) : _data{}, _pointer{ _data }  {}
        ~stack_allocator(void);

        memory_block allocate(uint32_t bytes) final override;
        void deallocate(const memory_block& memory_block) final override;
        void deallocate_all();

        bool owns(const memory_block& memory_block) const final override;
        bool expand(memory_block&, uint32_t bytes) final override;
        #pragma endregion

    private:
        #pragma region variables
        uint8_t _data[Size];
        uint8_t* _pointer;
        #pragma endregion

        #pragma region methods
        bool has_capacity(uint32_t bytes) const;
        #pragma endregion
    };

    #pragma region template implementations
    template <uint32_t Size>
    stack_allocator<Size>::~stack_allocator()
    {
        if (_pointer != _data)
        {
            allocator::_error_callback("destructor invoked on stack_allocator with allocated memory\n");
        }
    }

    template <uint32_t Size>
    memory_block stack_allocator<Size>::allocate(const uint32_t bytes)
    {
        _pointer += bytes;
        return { _pointer - bytes, bytes };
    }

    template <uint32_t Size>
    void stack_allocator<Size>::deallocate(const memory_block& memory_block)
    {
        if ((memory_block._address + memory_block._bytes) == _pointer)
        {
            _pointer = memory_block._address;
        }
    }

    template <uint32_t Size>
    void stack_allocator<Size>::deallocate_all()
    {
        _pointer = _data;
    }

    template <uint32_t Size>
    bool stack_allocator<Size>::owns(const memory_block& memory_block) const
    {
        return (memory_block._address >= _data) && (memory_block._address < (_data + Size));
    }

    template <uint32_t Size>
    bool stack_allocator<Size>::expand(memory_block& memory_block, uint32_t bytes)
    {
        if (has_capacity(bytes))
        {
            allocate(bytes);
            return true;
        }
        return false;
    }

    template <uint32_t Size>
    bool stack_allocator<Size>::has_capacity(const uint32_t bytes) const
    {
        return bytes <= uint32_t((_data + Size) - _pointer);
    }
    #pragma endregion
}