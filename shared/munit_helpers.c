#include "munit_helpers.h"

// ############################################################################
// Helpers
// ############################################################################
//

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
