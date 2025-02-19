#pragma once

#define MUNIT_ENABLE_ASSERT_ALIASES

#include "munit/munit.h"

MunitSuite munit_suite(MunitTest *tests);

MunitTest munit_test(char *name, MunitTestFunc test_func);
