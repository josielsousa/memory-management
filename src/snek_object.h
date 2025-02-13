#include "unions.h"

snek_object_t *new_snek_integer(int value);

snek_object_t *new_snek_float(float value);

snek_object_t *new_snek_string(const char *value);

snek_object_t *new_snek_vector(snek_object_t *x, snek_object_t *y,
                               snek_object_t *z);
