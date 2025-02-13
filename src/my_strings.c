#include "my_strings.h"
#include <string.h>

// smart_append - append src to dest, but only if it fits
// in the buffer
//
// It's called a smart because the destination buffer is a fixed `64` bytes,
// and it:
// - checks for available space before appending
// - appends as much as possible if there's not enough space.
// - always ensures the buffer remains null-terminated.
// - returns a status indicating whether the full append was possible.
//
// Here are the steps:
// - [X] If the input is NULL, return 1 (failure)
// - [X] Create a constant to represent the max buffer size of `64` bytes
// - [X] Get the length of the source string using `strlen`
// - [X] Calculate the remaining space in the dest buffer. Notice that it stores
// its own lenght. Don't forget to account for the null terminator.
// - [X] If the src string is larger than the remaining space:
//   - [X] Copy as much of the src string as possible into the dest buffer using
//   `strncat`.
//   - [X] Update the dest buffer length to the max size.
//   - [X] Return `1` (failure) to indicate the full appen was not possible.
// - [X] Otherwise, if there's enough space:
//   - [X] Append the entire src string to the dest buffer using `strcat`.
//   - [X] Update the dest buffer length to the new size.
//   - [X] Return `0` (success) to indicate the full append was possible.
int smart_append(TextBuffer *dest, const char *src) {
  if (dest == NULL || src == NULL) {
    return 1;
  }

  const int MAX_BUFFER_SIZE = 64;
  int src_length = strlen(src);
  int remaining_space = sizeof(dest->buffer) - dest->length - 1;

  if (src_length > remaining_space) {
    strncat(dest->buffer, src, remaining_space);
    dest->length = MAX_BUFFER_SIZE - 1;
    return 1;
  }

  strcat(dest->buffer, src);
  dest->length += src_length;
  return 0;
}
