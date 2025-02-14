#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit_helpers.h"

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  int mark_sweep_result = munit_mark_sweep_tests_cases(argc, argv);
  if (mark_sweep_result != 0) {
    return mark_sweep_result;
  }

  return 0;
}
