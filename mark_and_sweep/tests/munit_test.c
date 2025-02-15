#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit_helpers.h"

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
  int mark_sweep_result = munit_mark_phase_tests_cases(argc, argv);
  if (mark_sweep_result != 0) {
    return mark_sweep_result;
  }

  int traces_result = munit_traces_tests_cases(argc, argv);
  if (traces_result != 0) {
    return traces_result;
  }

  int sweep_phase_result = munit_sweep_phase_tests_cases(argc, argv);
  if (sweep_phase_result != 0) {
    return sweep_phase_result;
  }

  return 0;
}
