#include "munit_helpers.h"
#include "src/snek_object.h"

static MunitResult test_snek_length_array(const MunitParameter params[],
                                          void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_array(5);
  assert_not_null(obj);
  assert_int(obj->kind, ==, ARRAY);
  assert_int(obj->data.v_array.size, ==, 5);

  assert_not_null(obj->data.v_array.elements);
  assert_null(obj->data.v_array.elements[0]);

  int len = snek_length(obj);
  assert_int(len, ==, 5);

  free(obj->data.v_array.elements);
  free(obj);

  return MUNIT_OK;
}

static MunitResult test_snek_length_int(const MunitParameter params[],
                                        void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_integer(42);
  assert_not_null(obj);
  assert_int(obj->kind, ==, INTEGER);
  assert_int(obj->data.v_int, ==, 42);

  int len = snek_length(obj);
  assert_int(len, ==, 1);

  free(obj);

  return MUNIT_OK;
}

static MunitResult test_snek_length_float(const MunitParameter params[],
                                          void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(42.0);
  assert_not_null(obj);
  assert_int(obj->kind, ==, FLOATS);
  assert_float(obj->data.v_float, ==, 42.0);

  int len = snek_length(obj);
  assert_int(len, ==, 1);

  free(obj);

  return MUNIT_OK;
}

static MunitResult test_snek_length_string(const MunitParameter params[],
                                           void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_string("Hello");
  assert_not_null(obj);
  assert_int(obj->kind, ==, STRING);
  assert_string_equal(obj->data.v_string, "Hello");

  int len = snek_length(obj);
  assert_int(len, ==, 5);

  free(obj->data.v_string);
  free(obj);

  return MUNIT_OK;
}

int munit_objects_length_tests_cases(int argc,
                                     char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("object_length/array", test_snek_length_array),
      munit_test("object_length/int", test_snek_length_int),
      munit_test("object_length/float", test_snek_length_float),
      munit_test("object_length/string", test_snek_length_string),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
