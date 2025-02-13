#include "unions.h"
#include <stdbool.h>

snek_object_t *new_snek_integer(int value);

snek_object_t *new_snek_float(float value);

snek_object_t *new_snek_string(const char *value);

snek_object_t *new_snek_vector(snek_object_t *x, snek_object_t *y,
                               snek_object_t *z);

snek_object_t *new_snek_array(size_t size);

bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value);

snek_object_t *snek_array_get(snek_object_t *obj, size_t index);
