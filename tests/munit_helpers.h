#pragma once

#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"

MunitSuite munit_suite(MunitTest *tests);

MunitTest munit_test(char *name, MunitTestFunc test_func);

int munit_misc_tests_cases(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_strings_tests_cases(int argc,
                              char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_structs_enums_cases(int argc,
                              char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_stack_heap_cases(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_stack_tests_cases(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_objects_tests_cases(int argc,
                              char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_objects_length_tests_cases(int argc,
                                     char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_objects_add_tests_cases(int argc,
                                  char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);
int munit_refcount_tests_cases(int argc,
                               char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);

int munit_mark_sweep_tests_cases(int argc,
                                 char *argv[MUNIT_ARRAY_PARAM(argc + 1)]);
