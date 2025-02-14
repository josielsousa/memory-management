#include "munit_helpers.h"
#include "src/snek_object.h"

static MunitResult test_snek_integer_add(const MunitParameter params[],
                                         void *data) {
  (void)params;
  (void)data;

  snek_object_t *one = new_snek_integer(1);
  snek_object_t *three = new_snek_integer(3);
  snek_object_t *four = snek_add(one, three);

  assert_not_null(four);
  assert_int(four->kind, ==, INTEGER);
  assert_int(four->data.v_int, ==, 4);

  free(one);
  free(three);
  free(four);

  return MUNIT_OK;
}

static MunitResult test_snek_float_add(const MunitParameter params[],
                                       void *data) {
  (void)params;
  (void)data;

  snek_object_t *one = new_snek_float(1.5);
  snek_object_t *three = new_snek_float(3.5);
  snek_object_t *five = snek_add(one, three);

  assert_not_null(five);
  assert_int(five->kind, ==, FLOATS);
  assert_float(five->data.v_float, ==, 1.5 + 3.5);

  free(one);
  free(three);
  free(five);

  return MUNIT_OK;
}

static MunitResult test_snek_string_add(const MunitParameter params[],
                                        void *data) {
  (void)params;
  (void)data;

  snek_object_t *hello = new_snek_string("hello");
  snek_object_t *world = new_snek_string(", world");
  snek_object_t *greeting = snek_add(hello, world);

  assert_not_null(greeting);
  assert_int(greeting->kind, ==, STRING);
  assert_string_equal(greeting->data.v_string, "hello, world");

  free(hello->data.v_string);
  free(hello);
  free(world->data.v_string);
  free(world);
  free(greeting->data.v_string);
  free(greeting);

  return MUNIT_OK;
}

static MunitResult test_snek_string_add_self(const MunitParameter params[],
                                             void *data) {
  (void)params;
  (void)data;

  snek_object_t *repeated = new_snek_string("(repeated)");
  snek_object_t *result = snek_add(repeated, repeated);

  assert_not_null(result);
  assert_int(result->kind, ==, STRING);
  assert_string_equal(result->data.v_string, "(repeated)(repeated)");

  free(repeated->data.v_string);
  free(repeated);
  free(result->data.v_string);
  free(result);

  return MUNIT_OK;
}

static MunitResult test_snek_vector3_add(const MunitParameter params[],
                                         void *data) {
  (void)params;
  (void)data;

  snek_object_t *one = new_snek_float(1.0);
  snek_object_t *two = new_snek_float(2.0);
  snek_object_t *three = new_snek_float(3.0);
  snek_object_t *four = new_snek_float(4.0);
  snek_object_t *five = new_snek_float(5.0);
  snek_object_t *six = new_snek_float(6.0);

  snek_object_t *v1 = new_snek_vector(one, two, three);
  snek_object_t *v2 = new_snek_vector(four, five, six);
  snek_object_t *result = snek_add(v1, v2);

  free(v1->data.v_vector3.x);
  free(v1->data.v_vector3.y);
  free(v1->data.v_vector3.z);
  free(v1);

  free(v2->data.v_vector3.x);
  free(v2->data.v_vector3.y);
  free(v2->data.v_vector3.z);
  free(v2);

  free(result->data.v_vector3.x);
  free(result->data.v_vector3.y);
  free(result->data.v_vector3.z);
  free(result);

  return MUNIT_OK;
}

static MunitResult test_snek_array_add(const MunitParameter params[],
                                       void *data) {
  (void)params;
  (void)data;

  snek_object_t *one = new_snek_integer(1);
  snek_object_t *ones = new_snek_array(2);
  assert(snek_array_set(ones, 0, one));
  assert(snek_array_set(ones, 1, one));

  snek_object_t *hi = new_snek_string("hi");
  snek_object_t *hellos = new_snek_array(3);
  assert(snek_array_set(hellos, 0, hi));
  assert(snek_array_set(hellos, 1, hi));
  assert(snek_array_set(hellos, 2, hi));

  snek_object_t *result = snek_add(ones, hellos);

  assert_not_null(result);
  assert_int(result->kind, ==, ARRAY);

  snek_object_t *first = snek_array_get(result, 0);
  assert_not_null(first);
  assert_int(first->data.v_int, ==, 1);

  snek_object_t *third = snek_array_get(result, 2);
  assert_not_null(third);
  assert_string_equal(third->data.v_string, "hi");

  free(one);
  free(ones->data.v_array.elements);
  free(ones);

  free(hi->data.v_string);
  free(hi);
  free(hellos->data.v_array.elements);
  free(hellos);
  free(result->data.v_array.elements);
  free(result);
  return MUNIT_OK;
}

int munit_objects_add_tests_cases(int argc,
                                  char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("object_add/integer_add", test_snek_integer_add),
      munit_test("object_add/float_add", test_snek_float_add),
      munit_test("object_add/string_add", test_snek_string_add),
      munit_test("object_add/string_add_self", test_snek_string_add_self),
      munit_test("object_add/vector3_add", test_snek_vector3_add),
      munit_test("object_add/array_add", test_snek_array_add),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
