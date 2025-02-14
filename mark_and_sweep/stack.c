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
    free(stack);
    return NULL;
  }

  return stack;
}

void stack_push(stack_t *stack, void *value) {
  if (stack->count == stack->capacity) {
    stack->capacity *= 2;

    stack->data = realloc(stack->data, sizeof(void *) * stack->capacity);
    if (stack->data == NULL) {
      stack->capacity /= 2;
      return;
    }
  }

  stack->data[stack->count] = value;
  stack->count++;
}

void *stack_pop(stack_t *stack) {
  if (stack->count == 0) {
    return NULL;
  }

  stack->count--;

  return stack->data[stack->count];
}

void free_stack(stack_t *stack) {
  if (stack == NULL) {
    return;
  }

  if (stack->data != NULL) {
    free(stack->data);
  }

  free(stack);
}

void scary_double_push(stack_t *stack) {
  stack_push(stack, (void *)1337);

  int *ptr = (int *)malloc(sizeof(int));
  *ptr = 42;
  stack_push(stack, ptr);
}

void stack_remove_nulls(stack_t *stack) {
  size_t new_count = 0;

  // Update the count to reflect the new number of elements.
  for (size_t i = 0; i < stack->count; i++) {
    if (stack->data[i] != NULL) {
      stack->data[new_count++] = stack->data[i];
    }
  }

  // Update the count to reflect the new number of elements.
  stack->count = new_count;

  // Optionally, you might want to zero out the remaining slots.
  for (size_t i = new_count; i < stack->capacity; i++) {
    stack->data[i] = NULL;
  }
}
