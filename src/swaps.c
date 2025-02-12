#include "swaps.h"
#include <string.h>

void swap_ints(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Remember, `char **a` is a pointer to a pointer to a char `pointer`.
void swap_strings(char **a, char **b) {
  // this dereference the pointer to get the value
  // in this case, the value is a pointer
  char *temp = *a;

  *a = *b;
  *b = temp;
}

void swap(void *vp1, void *vp2, size_t size) {
  void *temp = malloc(size);
  if (temp == NULL) {
    return;
  }

  // copy the content of vp1 to temp
  memcpy(temp, vp1, size);

  // copy the content of vp2 to vp1
  memcpy(vp1, vp2, size);

  // copy the content of temp to vp2
  memcpy(vp2, temp, size);

  // it's important to free the memory allocated
  // else its will be a memory leak
  free(temp);
}
