#include "stack.h"
#include <stdlib.h>

stack_t *new_stack(size_t capacity) {
  stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->capacity = capacity;
  stack->data = malloc(sizeof(void *) * capacity);

  if (stack->data == NULL) {
    return NULL;
  }

  return stack;
}

void stack_push(stack_t *stack, void *value) {
  if (stack->count == stack->capacity) {
    stack->capacity *= 2;
    stack->data = realloc(stack->data, sizeof(void *) * stack->capacity);

    if (stack->data == NULL) {
      return;
    }
  }

  stack->data[stack->count] = value;
  stack->count++;
}
