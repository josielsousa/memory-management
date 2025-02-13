#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"
#include "munit_helpers.h"
#include "src/snek_object.h"

static MunitResult test_new_snek_integer(const MunitParameter params[],
                                         void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_integer(42);
  assert_not_null(obj);
  assert_int(obj->kind, ==, INTEGER);
  assert_int(obj->data.v_int, ==, 42);

  free(obj);

  return MUNIT_OK;
}

static MunitResult test_new_snek_float(const MunitParameter params[],
                                       void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_float(42.0);
  assert_not_null(obj);
  assert_int(obj->kind, ==, FLOATS);
  assert_float(obj->data.v_float, ==, 42.0);

  free(obj);

  return MUNIT_OK;
}

static MunitResult test_new_snek_string(const MunitParameter params[],
                                        void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_string("Hello");
  assert_not_null(obj);
  assert_int(obj->kind, ==, STRING);
  assert_string_equal(obj->data.v_string, "Hello");

  free(obj->data.v_string);
  free(obj);

  return MUNIT_OK;
}

static MunitResult test_new_snek_vector(const MunitParameter params[],
                                        void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj_null = new_snek_vector(NULL, NULL, NULL);
  assert_null(obj_null);

  snek_object_t *x = new_snek_integer(1);
  snek_object_t *y = new_snek_integer(2);
  snek_object_t *z = new_snek_integer(3);

  snek_object_t *obj = new_snek_vector(x, y, z);
  assert_not_null(obj);
  assert_int(obj->kind, ==, VECTOR3);
  assert_int(obj->data.v_vector3.x->data.v_int, ==, 1);
  assert_int(obj->data.v_vector3.y->data.v_int, ==, 2);
  assert_int(obj->data.v_vector3.z->data.v_int, ==, 3);

  free(obj->data.v_vector3.x);
  free(obj->data.v_vector3.y);
  free(obj->data.v_vector3.z);
  free(obj);

  return MUNIT_OK;
}

static MunitResult test_new_snek_array(const MunitParameter params[],
                                       void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_array(5);
  assert_not_null(obj);
  assert_int(obj->kind, ==, ARRAY);
  assert_int(obj->data.v_array.size, ==, 5);

  assert_not_null(obj->data.v_array.elements);
  assert_null(obj->data.v_array.elements[0]);

  free(obj->data.v_array.elements);
  free(obj);

  return MUNIT_OK;
}

int munit_objects_tests_cases(int argc,
                              char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("stack/test_new_snek_integer", test_new_snek_integer),
      munit_test("stack/test_new_snek_float", test_new_snek_float),
      munit_test("stack/test_new_snek_string", test_new_snek_string),
      munit_test("stack/test_new_snek_vector", test_new_snek_vector),
      munit_test("stack/test_new_snek_array", test_new_snek_array),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
