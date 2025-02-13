#include "snek_object.h"
#include <stdlib.h>
#include <string.h>

snek_object_t *_new_snek_object(void) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->refcount = 1;
  return obj;
}

snek_object_t *new_snek_integer(int value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = INTEGER;
  obj->data.v_int = value;

  return obj;
}

snek_object_t *new_snek_float(float value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = FLOATS;
  obj->data.v_float = value;

  return obj;
}

snek_object_t *new_snek_string(const char *value) {
  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = STRING;
  obj->data.v_string = malloc(strlen(value) + 1);

  if (obj->data.v_string == NULL) {
    return NULL;
  }

  strcpy(obj->data.v_string, value);

  return obj;
}

snek_object_t *new_snek_vector(snek_object_t *x, snek_object_t *y,
                               snek_object_t *z) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }

  snek_object_t *obj = _new_snek_object();
  if (obj == NULL) {
    return NULL;
  }

  obj->kind = VECTOR3;
  obj->data.v_vector3.x = x;
  obj->data.v_vector3.y = y;
  obj->data.v_vector3.z = z;

  return obj;
}

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *new_array = _new_snek_object();
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

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
  if (a == NULL || b == NULL) {
    return NULL;
  }

  switch (a->kind) {
  case INTEGER:
    switch (b->kind) {
    case INTEGER:
      return new_snek_integer(a->data.v_int + b->data.v_int);
    case FLOATS:
      return new_snek_float((float)a->data.v_int + b->data.v_float);
    default:
      return NULL;
    }
  case FLOATS:
    switch (b->kind) {
    case INTEGER:
      return new_snek_float(a->data.v_float + (float)b->data.v_int);
    case FLOATS:
      return new_snek_float(a->data.v_float + b->data.v_float);
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

    snek_object_t *obj = new_snek_string(str);
    free(str);

    return obj;
  case VECTOR3:
    if (b->kind != VECTOR3) {
      return NULL;
    }

    return new_snek_vector(snek_add(a->data.v_vector3.x, b->data.v_vector3.x),
                           snek_add(a->data.v_vector3.y, b->data.v_vector3.y),
                           snek_add(a->data.v_vector3.z, b->data.v_vector3.z));
  case ARRAY:
    if (b->kind != ARRAY) {
      return NULL;
    }

    size_t size = a->data.v_array.size + b->data.v_array.size;
    snek_object_t *newarray = new_snek_array(size);
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
