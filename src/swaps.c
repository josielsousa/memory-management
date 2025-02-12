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
