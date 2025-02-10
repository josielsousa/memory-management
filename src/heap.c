#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

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

// Complete the `allocate_scallar_list` function to allocate a list of integers,
// it should:
// - [X] Accept a size and a multiplier as arguments, and should allocate an
// array of integers on the heap.
// - [X] Gracefully handle allocation failures, returning NULL in such cases.
// - [X] Initialize the array with the first `size` multiples of the
// `multiplier`.
int *allocate_scallar_list(int size, int multiplier) {
  int *list = (int *)malloc(size * sizeof(int));

  if (list == NULL) {
    return NULL;
  }

  for (int i = 0; i < size; i++) {
    list[i] = i * multiplier;
  }

  return list;
}
