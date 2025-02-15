#include "snek_object.h"
#include <stdlib.h>
#include <string.h>

snek_object_t *_new_snek_object(vm_t *vm) {
  snek_object_t *obj = calloc(1, sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  vm_track_object(vm, obj);
  obj->is_marked = false;

  return obj;
}

snek_object_t *new_snek_integer(vm_t *vm, int value) {
  snek_object_t *new_int = _new_snek_object(vm);
  if (new_int == NULL) {
    return NULL;
  }

  new_int->kind = INTEGER;
  new_int->data.v_int = value;

  return new_int;
}

snek_object_t *new_snek_float(vm_t *vm, float value) {
  snek_object_t *new_float = _new_snek_object(vm);
  if (new_float == NULL) {
    return NULL;
  }

  new_float->kind = FLOATS;
  new_float->data.v_float = value;

  return new_float;
}

snek_object_t *new_snek_string(vm_t *vm, const char *value) {
  snek_object_t *new_str = _new_snek_object(vm);
  if (new_str == NULL) {
    return NULL;
  }

  new_str->kind = STRING;
  new_str->data.v_string = malloc(strlen(value) + 1);

  if (new_str->data.v_string == NULL) {
    return NULL;
  }

  strcpy(new_str->data.v_string, value);

  return new_str;
}

snek_object_t *new_snek_vector(vm_t *vm, snek_object_t *x, snek_object_t *y,
                               snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *new_vec = _new_snek_object(vm);
  if (new_vec == NULL) {
    return NULL;
  }

  new_vec->kind = VECTOR3;
  new_vec->data.v_vector3.x = x;
  new_vec->data.v_vector3.y = y;
  new_vec->data.v_vector3.z = z;

  return new_vec;
}

snek_object_t *new_snek_array(vm_t *vm, size_t size) {
  snek_object_t *new_array = _new_snek_object(vm);
  if (new_array == NULL) {
    return NULL;
  }

  new_array->kind = ARRAY;
  new_array->data.v_array.size = size;

  snek_object_t **elements = calloc(sizeof(snek_object_t *), size);
  if (elements == NULL) {
    return NULL;
  }

  snek_array_t array = {size, elements};
  new_array->data.v_array = array;

  return new_array;
}

bool snek_array_set(snek_object_t *obj, size_t index, snek_object_t *value) {
  if (obj == NULL || value == NULL || obj->kind != ARRAY) {
    return false;
  }

  if (index >= obj->data.v_array.size) {
    return false;
  }

  obj->data.v_array.elements[index] = value;
  return true;
}

snek_object_t *snek_array_get(snek_object_t *obj, size_t index) {
  if (obj == NULL || obj->kind != ARRAY) {
    return NULL;
  }

  if (index >= obj->data.v_array.size) {
    return NULL;
  }

  return obj->data.v_array.elements[index];
}

int snek_length(snek_object_t *obj) {
  if (obj == NULL) {
    return -1;
  }

  switch (obj->kind) {
  case INTEGER:
    return 1;
  case FLOATS:
    return 1;
  case STRING:
    return strlen(obj->data.v_string);
  case VECTOR3:
    return 3;
  case ARRAY:
    return obj->data.v_array.size;
  default:
    return -1;
  }
}

snek_object_t *snek_add(vm_t *vm, snek_object_t *a, snek_object_t *b) {
  if (a == NULL || b == NULL) {
    return NULL;
  }

  switch (a->kind) {
  case INTEGER:
    switch (b->kind) {
    case INTEGER:
      return new_snek_integer(vm, a->data.v_int + b->data.v_int);
    case FLOATS:
      return new_snek_float(vm, (float)a->data.v_int + b->data.v_float);
    default:
      return NULL;
    }
  case FLOATS:
    switch (b->kind) {
    case INTEGER:
      return new_snek_float(vm, a->data.v_float + (float)b->data.v_int);
    case FLOATS:
      return new_snek_float(vm, a->data.v_float + b->data.v_float);
    default:
      return NULL;
    }
  case STRING:
    if (b->kind != STRING) {
      return NULL;
    }

    size_t len = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;
    char *str = calloc(sizeof(char), len);

    strcat(str, a->data.v_string);
    strcat(str, b->data.v_string);

    snek_object_t *obj = new_snek_string(vm, str);
    free(str);

    return obj;
  case VECTOR3:
    if (b->kind != VECTOR3) {
      return NULL;
    }

    return new_snek_vector(
        vm, snek_add(vm, a->data.v_vector3.x, b->data.v_vector3.x),
        snek_add(vm, a->data.v_vector3.y, b->data.v_vector3.y),
        snek_add(vm, a->data.v_vector3.z, b->data.v_vector3.z));
  case ARRAY:
    if (b->kind != ARRAY) {
      return NULL;
    }

    size_t size = a->data.v_array.size + b->data.v_array.size;
    snek_object_t *newarray = new_snek_array(vm, size);
    if (newarray == NULL) {
      return NULL;
    }

    for (size_t i = 0; i < a->data.v_array.size; i++) {
      snek_array_set(newarray, i, snek_array_get(a, i));
    }

    for (size_t i = 0; i < b->data.v_array.size; i++) {
      snek_array_set(newarray, i + a->data.v_array.size, snek_array_get(b, i));
    }

    return newarray;
  default:
    return NULL;
  }
}

void snek_object_free(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }

  switch (obj->kind) {
  case INTEGER:
    break;
  case FLOATS:
    break;
  case STRING:
    free(obj->data.v_string);
    break;
  case VECTOR3:
    break;
  case ARRAY:
    free(obj->data.v_array.elements);
    break;
  }

  free(obj);
}
