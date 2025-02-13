#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"
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

int munit_objects_add_tests_cases(int argc,
                                  char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("object_add/integer_add", test_snek_integer_add),
      munit_test("object_add/float_add", test_snek_float_add),
      munit_test("object_add/string_add", test_snek_string_add),
      munit_test("object_add/string_add_self", test_snek_string_add_self),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
