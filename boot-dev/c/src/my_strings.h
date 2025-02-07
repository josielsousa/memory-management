#include <string.h>

#pragma once

typedef struct {
  size_t length;
  char buffer[64];
} TextBuffer;

int smart_append(TextBuffer *dest, const char *src);
