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

const MunitTest munit_null_test = {
    NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL
};

MunitTest munit_test(char *name, MunitTestFunc test_func)
{
    MunitTest test = {name, test_func, NULL, NULL, MUNIT_TEST_OPTION_NONE,
                      NULL};

    return test;
}

MunitSuite munit_suite(MunitTest *tests)
{
    MunitSuite suite = {
        (char *)"", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE,
    };

    return suite;
}

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)])
{
    MunitTest test_suite_tests[] = {
        munit_test("main/test_compate_integer", test_compare_integer),
        munit_test("main/test_get_language", test_get_language),
        munit_null_test,
    };

    MunitSuite test_suite = munit_suite(test_suite_tests);

    return munit_suite_main(&test_suite, NULL, argc, argv);
}
