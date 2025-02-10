#include <stdbool.h>

#pragma once

bool is_on_stack(void *ptr);

int *allocate_scallar_list(int size, int multiplier);
