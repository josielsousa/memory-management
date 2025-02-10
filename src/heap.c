#include <stdbool.h>
#include <stdint.h>

bool is_on_stack(void *ptr) {
  void *stack_top = __builtin_frame_address(0);
  uintptr_t stack_top_addr = (uintptr_t)stack_top;
  uintptr_t ptr_addr = (uintptr_t)ptr;

  // check within a threshold in both directions(e.g 1024 bytes)
  uintptr_t threshold = 1024;

  // check if the pointer is within the stack range
  // above or below the stack top;
  bool is_on_stack = ptr_addr >= (stack_top_addr - threshold) &&
                     ptr_addr <= (stack_top_addr + threshold);

  return is_on_stack;
}
