#pragma once

#include <stddef.h>

typedef struct Stack {
  int count;
  int capacity;
  void **data;
} stack_t;

stack_t *new_stack(size_t capacity);
