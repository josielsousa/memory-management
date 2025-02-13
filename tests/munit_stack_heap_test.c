#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"
#include "munit_helpers.h"
#include "src/heap.h"
#include "src/node.h"
#include "src/pointers.h"
#include "src/snek_object.h"
#include "src/swaps.h"

static MunitResult test_unions_snek_object(const MunitParameter params[],
                                           void *data) {
  (void)params;
  (void)data;

  snek_object_t obj = new_integer(42);
  assert_int(obj.kind, ==, INTEGER);
  assert_int(obj.data.v_int, ==, 42);

  snek_object_t obj2 = new_string("Hello");
  assert_int(obj2.kind, ==, STRING);
  assert_string_equal(obj2.data.v_string, "Hello");

  char buffer[15];
  format_object(obj, buffer);
  assert_string_equal(buffer, "integer:42\n");

  format_object(obj2, buffer);
  assert_string_equal(buffer, "string:Hello\n");

  snek_object_t obj_unknown = {0};
  format_object(obj_unknown, buffer);
  assert_string_equal(buffer, "unknown\n");

  return MUNIT_OK;
}

static MunitResult test_is_pointer_on_stack(const MunitParameter params[],
                                            void *data) {
  (void)params;
  (void)data;

  int value = 42;
  int *ptr = &value;

  assert_true(is_on_stack(ptr));

  employee_t *engineer = new_employee(2, "John Doe", NULL);
  assert_false(is_on_stack(engineer));
  free(engineer);

  return MUNIT_OK;
}

static MunitResult test_allocate_scallar_list(const MunitParameter params[],
                                              void *data) {
  (void)params;
  (void)data;

  int *list = allocate_scallar_list(5, 2);
  int expected[5] = {0, 2, 4, 6, 8};

  for (int i = 0; i < 5; i++) {
    assert_int(list[i], ==, expected[i]);
  }

  free(list);

  return MUNIT_OK;
}

static MunitResult
test_allocate_scallar_list_zero(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  int *list = allocate_scallar_list(5, 0);
  int expected[5] = {0, 0, 0, 0, 0};

  for (int i = 0; i < 5; i++) {
    assert_int(list[i], ==, expected[i]);
  }

  free(list);

  return MUNIT_OK;
}

static MunitResult test_snek_zero_out(const MunitParameter params[],
                                      void *data) {
  (void)params;
  (void)data;

  snek_int_t integer = {.name = "value", .value = 42};
  snek_zero_out(&integer, INT);
  assert_int(integer.value, ==, 0);

  snek_float_t floating = {.name = "value", .value = 3.14};
  snek_zero_out(&floating, FLOAT);
  assert_float(floating.value, ==, 0.0);

  snek_bool_t boolean = {.name = "value", .value = true};
  snek_zero_out(&boolean, BOOL);
  assert_false(boolean.value);

  return MUNIT_OK;
}

static MunitResult test_swap_ints(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  int a = 10;
  int b = 20;

  swap_ints(&a, &b);

  assert_int(a, ==, 20);
  assert_int(b, ==, 10);

  return MUNIT_OK;
}

static MunitResult test_swap_strings(const MunitParameter params[],
                                     void *data) {
  (void)params;
  (void)data;

  char *a = "Hello";
  char *b = "World";

  swap_strings(&a, &b);

  assert_string_equal(a, "World");
  assert_string_equal(b, "Hello");

  return MUNIT_OK;
}

static MunitResult test_swap(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  int a = 10;
  int b = 20;

  swap(&a, &b, sizeof(int));

  assert_int(a, ==, 20);
  assert_int(b, ==, 10);

  // swap strings
  char *str1 = "Hello";
  char *str2 = "World";

  swap(&str1, &str2, sizeof(char *));
  assert_string_equal(str1, "World");
  assert_string_equal(str2, "Hello");

  // swap custom type
  snek_int_t integer1 = {.name = "value", .value = 42};
  snek_int_t integer2 = {.name = "value", .value = 24};

  swap(&integer1, &integer2, sizeof(snek_int_t));
  assert_int(integer1.value, ==, 24);
  assert_int(integer2.value, ==, 42);

  return MUNIT_OK;
}

int munit_stack_heap_cases(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("stack_heap/test_unions_snek_object", test_unions_snek_object),
      munit_test("stack_heap/test_is_pointer_on_stack",
                 test_is_pointer_on_stack),
      munit_test("stack_heap/test_allocate_scallar_list",
                 test_allocate_scallar_list),
      munit_test("stack_heap/test_allocate_scallar_list_zero",
                 test_allocate_scallar_list_zero),
      munit_test("stack_heap/test_snek_zero_out", test_snek_zero_out),
      munit_test("stack_heap/test_swap_ints", test_swap_ints),
      munit_test("stack_heap/test_swap_strings", test_swap_strings),
      munit_test("stack_heap/test_swap", test_swap),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
