### allocators

- [x] malloc allocator
- [x] stack allocator
- [x] fallback allocator

### usage

```cpp
  mcpgnz::stack_allocator<32> allocator{};
  const auto memory = allocator.allocate(sizeof(uint32_t));
  const auto value = (uint32_t*)memory._address;

  *value = 13;

  std::cout << "[single_allocation] value: " << *value << '\n';
  allocator.deallocate(memory);
```
