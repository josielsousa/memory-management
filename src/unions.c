#include "snek_object.h"
#include <stdio.h>

void format_object(snek_object_t obj, char *buffer) {
  switch (obj.kind) {
  case INTEGER:
    sprintf(buffer, "integer:%d\n", obj.data.v_int);
    return;
  case STRING:
    sprintf(buffer, "string:%s\n", obj.data.v_string);
    return;
  default:
    sprintf(buffer, "unknown\n");
  }
}

snek_object_t new_integer(int value) {
  return (snek_object_t){
      .kind = INTEGER,
      .data =
          (snek_object_data_t){
              .v_int = value,
          },
  };
}
snek_object_t new_string(const char *value) {
  return (snek_object_t){
      .kind = STRING,
      .data =
          (snek_object_data_t){
              .v_string = (char *)value,
          },
  };
}
