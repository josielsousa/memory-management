#define MUNIT_ENABLE_ASSERT_ALIASES
#include "../munit/munit.h"

static MunitResult test_compare(const MunitParameter params[], void *data) {
    (void)params;
    (void)data;

    assert_int(1, ==, 1);

    return MUNIT_OK;
}

/* The setup function, if you provide one, for a test will be run
 * before the test, and the return value will be passed as the sole
 * parameter to the test function. */
static void *test_compare_setup(const MunitParameter params[],
                                void                *user_data) {
    (void)params;
    (void)user_data;

    return (void *)(uintptr_t)0xdeadbeef;
}

/* To clean up after a test, you can use a tear down function.  The
 * fixture argument is the value returned by the setup function
 * above. */
static void test_compare_tear_down(void *fixture) {
    munit_assert_ptr_equal(fixture, (void *)(uintptr_t)0xdeadbeef);
}

/* Creating a test suite is pretty simple.  First, you'll need an
 * array of tests: */
static MunitTest test_suite_tests[] = {
    {// The name is just a unique human-readable way to identify the test
     (char *)"test_compare",
     /* You probably won't be surprised to learn that the tests are
      * functions. */
     test_compare,
     /* If you want, you can supply a function to set up a fixture.  If
      * you supply NULL, the user_data parameter from munit_suite_main
      * will be used directly.  If, however, you provide a callback
      * here the user_data parameter will be passed to this callback,
      * and the return value from this callback will be passed to the
      * test function.
      *
      * For our example we don't really need a fixture, but lets
      * provide one anyways. */
     test_compare_setup,
     /* If you passed a callback for the fixture setup function, you
      * may want to pass a corresponding callback here to reverse the
      * operation. */
     test_compare_tear_down,
     /* Finally, there is a bitmask for options you can pass here.  You
      * can provide either MUNIT_TEST_OPTION_NONE or 0 here to use the
      * defaults. */
     MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Now we'll actually declare the test suite.  You could do this in
 * the main function, or on the heap, or whatever you want. */
static const MunitSuite test_suite = {
    // This string will be prepended to all test names in this suite;
    (char *)"",
    // The first parameter is the array of test suites.
    test_suite_tests,
    // In addition to containing test cases, suites can contain other
    // test suites.
    NULL,
    // multiple iterations of the tests
    1,
    /* Just like MUNIT_TEST_OPTION_NONE, you can provide
     * MUNIT_SUITE_OPTION_NONE or 0 to use the default settings. */
    MUNIT_SUITE_OPTION_NONE,
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    /* Finally, we'll actually run our test suite!  That second argument
     * is the user_data parameter which will be passed either to the
     * test or (if provided) the fixture setup function. */
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
