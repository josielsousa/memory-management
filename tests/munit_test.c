#define MUNIT_ENABLE_ASSERT_ALIASES
#include "../boot-dev/c/src/main.h"
#include "../munit/munit.h"

// test_compare_integer - compare an integer to itself
static MunitResult
test_compare_integer(const MunitParameter params[], void *data)
{
    (void)params;
    (void)data;

    assert_int(1, ==, 1);

    return MUNIT_OK;
}

// test_get_language - assert that  get_language returns "C"
static MunitResult test_get_language(const MunitParameter params[], void *data)
{
    (void)params;
    (void)data;

    char *language = get_language();
    assert_string_equal(language, "C");

    return MUNIT_OK;
}

// Creating a test suite is pretty simple.  First, you'll need an
// array of tests:
static MunitTest test_suite_tests[] = {
    {(char *)"test_compare", test_compare_integer, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {(char *)"test_get_language", test_get_language, NULL, NULL,
     MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite test_suite = {
    // This string will be prepended to all test names in this suite;
    (char *)"main/",
    // The first parameter is the array of test suites.
    test_suite_tests,
    // In addition to containing test cases, suites can contain other
    // test suites.
    NULL,
    // multiple iterations of the tests
    1,
    // Just like MUNIT_TEST_OPTION_NONE, you can provide
    // MUNIT_SUITE_OPTION_NONE or 0 to use the default settings.
    MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
