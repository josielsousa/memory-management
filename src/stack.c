#include "stack.h"
#include <stdlib.h>

stack_t *new_stack(size_t capacity) {
  stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->capacity = capacity;
  stack->data = (void **)malloc(sizeof(void *) * capacity);

  if (stack->data == NULL) {
    return NULL;
  }

  return stack;
}
