#pragma once

#include <stddef.h>

typedef struct Stack {
  int count;
  int capacity;
  void **data;
} stack_t;

stack_t *new_stack(size_t capacity);

void stack_push(stack_t *stack, void *value);

void *stack_pop(stack_t *stack);

void free_stack(stack_t *stack);

void scary_double_push(stack_t *stack);

void stack_remove_nulls(stack_t *stack);
