#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"
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

  free(obj->data.v_array.elements);
  free(obj);

  return MUNIT_OK;
}

int munit_objects_length_tests_cases(int argc,
                                     char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests_misc[] = {
      munit_test("object_length/array", test_snek_length_array),
      {.name = NULL,
       .test = NULL,
       .setup = NULL,
       .tear_down = NULL,
       .options = MUNIT_TEST_OPTION_NONE,
       .parameters = NULL}};

  MunitSuite test_suite_misc = munit_suite(test_suite_tests_misc);

  return munit_suite_main_custom(&test_suite_misc, NULL, argc, argv, NULL);
}
