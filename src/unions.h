#pragma once

typedef enum SnekObjectKind {
  INTEGER = 1,
  STRING = 2,
} snek_object_kind_t;

typedef union SnekObjectData {
  int v_int;
  char *v_string;
} snek_object_data_t;

typedef struct SnekObject {
  snek_object_kind_t kind;
  snek_object_data_t data;
} snek_object_t;

void format_object(snek_object_t obj, char *buffer);

snek_object_t new_integer(int value);

snek_object_t new_string(const char *value);
