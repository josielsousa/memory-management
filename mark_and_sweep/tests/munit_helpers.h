#pragma once

#include "shared/munit_helpers.h"

int munit_mark_phase_tests_cases(int argc,
                                 char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_traces_tests_cases(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_sweep_phase_tests_cases(int argc,
                                  char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);
