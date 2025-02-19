#include "munit_helpers.h"

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  int misc_result = munit_misc_tests_cases(argc, argv);
  if (misc_result != 0) {
    return misc_result;
  }

  int strings_result = munit_strings_tests_cases(argc, argv);
  if (strings_result != 0) {
    return strings_result;
  }

  int strenums_result = munit_structs_enums_cases(argc, argv);
  if (strenums_result != 0) {
    return strenums_result;
  }

  int stack_heap_result = munit_stack_heap_cases(argc, argv);
  if (stack_heap_result != 0) {
    return stack_heap_result;
  }

  int stack_result = munit_stack_tests_cases(argc, argv);
  if (stack_result != 0) {
    return stack_result;
  }

  int objects_result = munit_objects_tests_cases(argc, argv);
  if (objects_result != 0) {
    return objects_result;
  }

  int objects_length_result = munit_objects_length_tests_cases(argc, argv);
  if (objects_length_result != 0) {
    return objects_length_result;
  }

  int objects_add_result = munit_objects_add_tests_cases(argc, argv);
  if (objects_add_result != 0) {
    return objects_add_result;
  }

  int refcount_result = munit_refcount_tests_cases(argc, argv);
  if (refcount_result != 0) {
    return refcount_result;
  }

  return 0;
}
