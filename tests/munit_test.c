#define MUNIT_ENABLE_ASSERT_ALIASES
#include "../munit/munit.h"

#include "../boot-dev/c/src/main.h"

// ############################################################################
// Helpers
// ############################################################################
const MunitTest munit_null_test = {.name = NULL,
                                   .test = NULL,
                                   .setup = NULL,
                                   .tear_down = NULL,
                                   .options = MUNIT_TEST_OPTION_NONE,
                                   .parameters = NULL};

MunitTest munit_test(char *name, MunitTestFunc test_func) {
  return (MunitTest){.name = name,
                     .test = test_func,
                     .setup = NULL,
                     .tear_down = NULL,
                     .options = MUNIT_TEST_OPTION_NONE,
                     .parameters = NULL};
}

MunitSuite munit_suite(MunitTest *tests) {
  return (MunitSuite){
      .prefix = (char *)"",
      .tests = tests,
      .suites = NULL,
      .iterations = 1,
      .options = MUNIT_SUITE_OPTION_NONE,
  };
}

// ############################################################################
// Suite Cases - Tests
// ############################################################################

// test_compare_integer - compare an integer to itself
static MunitResult test_compare_integer(const MunitParameter params[],
                                        void *data) {
  (void)params;
  (void)data;

  assert_int(1, ==, 1);

  return MUNIT_OK;
}

// test_get_language - assert that  get_language returns "C"
static MunitResult test_get_language(const MunitParameter params[],
                                     void *data) {
  (void)params;
  (void)data;

  char *language = get_language();
  assert_string_equal(language, "C");

  return MUNIT_OK;
}

// test_new_coordinate - assert that new_coordinate returns a Coordinate
static MunitResult test_new_coordinate(const MunitParameter params[],
                                       void *data) {
  (void)params;
  (void)data;

  struct Coordinate coordinate = new_coordinate(1, 2, 3);
  assert_int(coordinate.x, ==, 1);
  assert_int(coordinate.y, ==, 2);
  assert_int(coordinate.z, ==, 3);

  return MUNIT_OK;
}

// test_scale_coordinate - assert that scale_coordinate returns a Coordinate
static MunitResult test_scale_coordinate(const MunitParameter params[],
                                         void *data) {
  (void)params;
  (void)data;

  struct Coordinate coordinate = new_coordinate(1, 2, 3);
  struct Coordinate scaled = scale_coordinate(coordinate, 2);

  assert_int(scaled.x, ==, 2);
  assert_int(scaled.y, ==, 4);
  assert_int(scaled.z, ==, 6);

  return MUNIT_OK;
}

// test_new_human - assert that new_human returns a Human
static MunitResult test_new_human(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  human_t human = new_human("John Doe", 30, 1);
  assert_string_equal(human.name, "John Doe");
  assert_int(human.age, ==, 30);
  assert_int(human.is_alive, ==, 1);

  return MUNIT_OK;
}

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  MunitTest test_suite_tests[] = {
      munit_test("main/test_compate_integer", test_compare_integer),
      munit_test("main/test_get_language", test_get_language),
      munit_test("main/test_new_coordinate", test_new_coordinate),
      munit_test("main/test_scale_coordinate", test_scale_coordinate),
      munit_test("main/test_new_human", test_new_human),
      munit_null_test,
  };

  MunitSuite test_suite = munit_suite(test_suite_tests);

  return munit_suite_main(&test_suite, NULL, argc, argv);
}
