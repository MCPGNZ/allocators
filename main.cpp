#include <iostream>
#include "source/stack_allocator.h"
#include "source/malloc_allocator.h"

struct allocator_examples
{
     /* uses stack allocator to allocate single uint32_t */
    static void single_allocation()
    {
        mcpgnz::stack_allocator<32> allocator{};
        const auto memory = allocator.allocate(sizeof(uint32_t));
        const auto value = (uint32_t*)memory._address;

        *value = 13;

        std::cout << "[single_allocation] value: " << *value << '\n';
        allocator.deallocate(memory);
    }

    /* provide custom error handler */
    static void error_handler()
    {
        /* provide custom callback */
        mcpgnz::allocator::_error_callback = [](const char* message)
        {
            std::cout << "[error_handler] something went wrong...\n";
        };

        /* leak memory from stack_allocator */
        mcpgnz::stack_allocator<32> allocator{};
        allocator.allocate(32);
    }
};

int main()
{
    allocator_examples::single_allocation();
    allocator_examples::error_handler();

    system("pause");
    return 0;
}