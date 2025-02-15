#pragma once

#include "shared/munit_helpers.h"

int munit_mark_sweep_tests_cases(int argc,
                                 char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_traces_tests_cases(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);
