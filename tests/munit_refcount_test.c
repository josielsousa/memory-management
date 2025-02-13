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
  assert_int(obj->refcount, ==, 1);

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
  assert_int(obj->refcount, ==, 1);

  free(obj);

  return MUNIT_OK;
}

static MunitResult test_refcount_increment(const MunitParameter params[],
                                           void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_integer(42);
  assert_not_null(obj);
  assert_int(obj->refcount, ==, 1);

  refcount_incr(obj);
  assert_int(obj->refcount, ==, 2);

  free(obj);

  return MUNIT_OK;
}

static MunitResult test_refcount_increment_null(const MunitParameter params[],
                                                void *data) {
  (void)params;
  (void)data;

  refcount_incr(NULL);
  assert(1);

  return MUNIT_OK;
}

static MunitResult test_refcount_decrement(const MunitParameter params[],
                                           void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_integer(42);
  assert_not_null(obj);
  assert_int(obj->refcount, ==, 1);

  refcount_incr(obj);
  assert_int(obj->refcount, ==, 2);

  refcount_decr(obj);
  assert_int(obj->refcount, ==, 1);

  free(obj);

  return MUNIT_OK;
}

static MunitResult test_refcount_decrement_string(const MunitParameter params[],
                                                  void *data) {
  (void)params;
  (void)data;

  snek_object_t *obj = new_snek_string("Hello @wagslane!");

  refcount_incr(obj);
  assert_int(obj->refcount, ==, 2);

  refcount_decr(obj);
  assert_int(obj->refcount, ==, 1);
  assert_string_equal(obj->data.v_string, "Hello @wagslane!");

  refcount_decr(obj);
  assert(1);

  return MUNIT_OK;
}

static MunitResult test_refcount_vector3(const MunitParameter params[],
                                         void *data) {
  (void)params;
  (void)data;

  snek_object_t *foo = new_snek_integer(1);
  snek_object_t *bar = new_snek_integer(2);
  snek_object_t *baz = new_snek_integer(3);

  snek_object_t *vec = new_snek_vector(foo, bar, baz);
  assert_int(foo->refcount, ==, 2);
  assert_int(bar->refcount, ==, 2);
  assert_int(baz->refcount, ==, 2);

  refcount_decr(foo);
  assert_int(foo->refcount, ==, 1);

  refcount_decr(vec);
  // vec->refcount ==, 0
  // foo->refcount ==, 0
  // at this point, foo should be freed

  // assert_int(bar->refcount, ==, 1);
  // assert_int(baz->refcount, ==, 1);
  //
  // refcount_decr(bar);
  // assert_int(bar->refcount, ==, 0);
  //
  // refcount_decr(baz);
  // assert_int(baz->refcount, ==, 0);

  return MUNIT_OK;
}

int munit_refcount_tests_cases(int argc,
                               char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("refcount/test_new_snek_integer", test_new_snek_integer),
      munit_test("refcount/test_new_snek_float", test_new_snek_float),
      munit_test("refcount/test_refcount_increment", test_refcount_increment),
      munit_test("refcount/test_refcount_increment_null",
                 test_refcount_increment_null),
      munit_test("refcount/test_refcount_decrement", test_refcount_decrement),
      munit_test("refcount/test_refcount_decrement_string",
                 test_refcount_decrement_string),
      munit_test("refcount/test_refcount_vector3", test_refcount_vector3),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
