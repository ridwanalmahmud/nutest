#ifndef __NUTEST_H__
#define __NUTEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <float.h>

// test result codes
typedef enum { TEST_PASS, TEST_FAIL, TEST_SKIP, TEST_ERROR } TestResult;

// test case function type
typedef TestResult (*TestFunc)(void);

// test case structure
typedef struct {
    const char *name;
    TestFunc function;
    const char *suite_name;
    const char *description;
} TestCase;

// test suite structure
typedef struct {
    const char *name;
    TestCase *tests;
    size_t test_count;
    const char *description;
} TestSuite;

// test registry
typedef struct {
    TestSuite *suites;
    size_t suite_count;
} TestRegistry;

// global test registry
static TestRegistry test_registry = {NULL, 0};

#define ASSERT_TRUE(condition)                                             \
    do {                                                                   \
        if (!(condition)) {                                                \
            fprintf(stderr,                                                \
                    "[  FAILED ] %s:%d: Expected: %s evaluates to true\n", \
                    __FILE__,                                              \
                    __LINE__,                                              \
                    #condition);                                           \
            return TEST_FAIL;                                              \
        }                                                                  \
    } while (0)

#define ASSERT_FALSE(condition)                                             \
    do {                                                                    \
        if (condition) {                                                    \
            fprintf(stderr,                                                 \
                    "[  FAILED ] %s:%d: Expected: %s evaluates to false\n", \
                    __FILE__,                                               \
                    __LINE__,                                               \
                    #condition);                                            \
            return TEST_FAIL;                                               \
        }                                                                   \
    } while (0)

#define ASSERT_EQ(expected, actual)                                       \
    do {                                                                  \
        if ((expected) != (actual)) {                                     \
            fprintf(stderr,                                               \
                    "[  FAILED ] %s:%d: Expected: %s == %s (%d vs %d)\n", \
                    __FILE__,                                             \
                    __LINE__,                                             \
                    #expected,                                            \
                    #actual,                                              \
                    (int)(expected),                                      \
                    (int)(actual));                                       \
            return TEST_FAIL;                                             \
        }                                                                 \
    } while (0)

#define ASSERT_NE(val1, val2)                                                \
    do {                                                                     \
        if ((val1) == (val2)) {                                              \
            fprintf(stderr,                                                  \
                    "[  FAILED ] %s:%d: Expected: %s != %s (both are %d)\n", \
                    __FILE__,                                                \
                    __LINE__,                                                \
                    #val1,                                                   \
                    #val2,                                                   \
                    (int)(val1));                                            \
            return TEST_FAIL;                                                \
        }                                                                    \
    } while (0)

#define ASSERT_FLOAT_EQ(expected, actual)                                   \
    do {                                                                    \
        float _expected = (expected);                                       \
        float _actual = (actual);                                           \
        float _diff = fabsf(_expected - _actual);                           \
        if (_diff > FLT_EPSILON) {                                          \
            fprintf(stderr,                                                 \
                    "[  FAILED ] %s:%d: Expected: %s == %s (%.9g vs %.9g, " \
                    "diff %.9g)\n",                                         \
                    __FILE__,                                               \
                    __LINE__,                                               \
                    #expected,                                              \
                    #actual,                                                \
                    _expected,                                              \
                    _actual,                                                \
                    _diff);                                                 \
            return TEST_FAIL;                                               \
        }                                                                   \
    } while (0)

#define ASSERT_DOUBLE_EQ(expected, actual)                                    \
    do {                                                                      \
        double _expected = (expected);                                        \
        double _actual = (actual);                                            \
        double _diff = fabs(_expected - _actual);                             \
        if (_diff > DBL_EPSILON) {                                            \
            fprintf(stderr,                                                   \
                    "[  FAILED ] %s:%d: Expected: %s == %s (%.17g vs %.17g, " \
                    "diff %.17g)\n",                                          \
                    __FILE__,                                                 \
                    __LINE__,                                                 \
                    #expected,                                                \
                    #actual,                                                  \
                    _expected,                                                \
                    _actual,                                                  \
                    _diff);                                                   \
            return TEST_FAIL;                                                 \
        }                                                                     \
    } while (0)

#define ASSERT_NEAR(expected, actual, tolerance)                              \
    do {                                                                      \
        double _expected = (expected);                                        \
        double _actual = (actual);                                            \
        double _diff = fabs(_expected - _actual);                             \
        if (_diff > (tolerance)) {                                            \
            fprintf(stderr,                                                   \
                    "[  FAILED ] %s:%d: Expected: %s ~= %s (%.17g vs %.17g, " \
                    "diff %.17g > tol %.17g)\n",                              \
                    __FILE__,                                                 \
                    __LINE__,                                                 \
                    #expected,                                                \
                    #actual,                                                  \
                    _expected,                                                \
                    _actual,                                                  \
                    _diff,                                                    \
                    (tolerance));                                             \
            return TEST_FAIL;                                                 \
        }                                                                     \
    } while (0)

#define ASSERT_NULL(ptr)                                        \
    do {                                                        \
        if (ptr != NULL) {                                      \
            fprintf(stderr,                                     \
                    "[  FAILED ] %s:%d: %s is not NULL (%p)\n", \
                    __FILE__,                                   \
                    __LINE__,                                   \
                    #ptr,                                       \
                    (void *)(ptr));                             \
            return TEST_FAIL;

#define ASSERT_NOT_NULL(ptr)                                \
    do {                                                    \
        if (ptr == NULL) {                                  \
            fprintf(stderr,                                 \
                    "[  FAILED ] %s:%d: %s is NULL (%p)\n", \
                    __FILE__,                               \
                    __LINE__,                               \
                    #ptr,                                   \
                    (void *)(ptr));                         \
            return TEST_FAIL;

#define ASSERT_MEM_EQ(expected, actual, size)                            \
    do {                                                                 \
        if (memcmp((expected), (actual), (size))) {                      \
            fprintf(stderr,                                              \
                    "[  FAILED ] %s:%d: Memory differs for %s and %s\n", \
                    __FILE__,                                            \
                    __LINE__,                                            \
                    #expected,                                           \
                    #actual);                                            \
            return TEST_FAIL;

// test registration macros
#define TEST_F(test_suite_name, test_name)                          \
    static TestResult test_suite_name##_##test_name(void);          \
    __attribute__((constructor)) static void                        \
    register_##test_suite_name##_##test_name(void) {                \
        static TestCase test_case = {#test_name,                    \
                                     test_suite_name##_##test_name, \
                                     #test_suite_name,              \
                                     NULL};                         \
        register_test_case(&test_case);                             \
    }                                                               \
    static TestResult test_suite_name##_##test_name(void)

#define TEST(test_suite_name, test_name) TEST_F(test_suite_name, test_name)

#define TEST_F_DESC(test_suite_name, test_name, description)        \
    static TestResult test_suite_name##_##test_name(void);          \
    __attribute__((constructor)) static void                        \
    register_##test_suite_name##_##test_name(void) {                \
        static TestCase test_case = {#test_name,                    \
                                     test_suite_name##_##test_name, \
                                     #test_suite_name,              \
                                     description};                  \
        register_test_case(&test_case);                             \
    }                                                               \
    static TestResult test_suite_name##_##test_name(void)

// fixture support
#define FIXTURE_TEST(test_suite_name, test_name) \
    TEST_F(test_suite_name, test_name)

// fixture support
#define FIXTURE(test_suite_name)                                        \
    typedef struct test_suite_name##_Fixture test_suite_name##_Fixture; \
    struct test_suite_name##_Fixture

#define SET_UP() static void SetUp(test_suite_name##_Fixture *fixture)

#define TEAR_DOWN() static void TearDown(test_suite_name##_Fixture *fixture)

#define FIXTURE_TEST_F(test_suite_name, test_name)                          \
    static TestResult test_suite_name##_##test_name##_Impl(                 \
        test_suite_name##_Fixture *fixture);                                \
    static TestResult test_suite_name##_##test_name(void) {                 \
        test_suite_name##_Fixture fixture;                                  \
        memset(&fixture, 0, sizeof(fixture));                               \
        SetUp(&fixture);                                                    \
        TestResult result = test_suite_name##_##test_name##_Impl(&fixture); \
        TearDown(&fixture);                                                 \
        return result;                                                      \
    }                                                                       \
    TEST_F(test_suite_name, test_name) {                                    \
        return test_suite_name##_##test_name();                             \
    }                                                                       \
    static TestResult test_suite_name##_##test_name##_Impl(                 \
        test_suite_name##_Fixture *fixture)

// skip test macro
#define SKIP() return TEST_SKIP

// performance measurement macros
#define BENCHMARK_START()                     \
    struct timespec _bench_start, _bench_end; \
    clock_gettime(CLOCK_MONOTONIC, &_bench_start)

#define BENCHMARK_END(name)                                                 \
    clock_gettime(CLOCK_MONOTONIC, &_bench_end);                            \
    double _bench_time = (_bench_end.tv_sec - _bench_start.tv_sec) +        \
                         (_bench_end.tv_nsec - _bench_start.tv_nsec) / 1e9; \
    printf("[ BENCHMARK ] %s: %.9f seconds\n", name, _bench_time)

// test registration function
static void register_test_case(TestCase *test_case) {
    // Find or create the test suite
    TestSuite *suite = NULL;
    for (size_t i = 0; i < test_registry.suite_count; i++) {
        if (strcmp(test_registry.suites[i].name, test_case->suite_name) == 0) {
            suite = &test_registry.suites[i];
            break;
        }
    }

    if (!suite) {
        // Create new suite
        test_registry.suite_count++;
        test_registry.suites =
            (TestSuite *)realloc(test_registry.suites,
                                 test_registry.suite_count * sizeof(TestSuite));
        suite = &test_registry.suites[test_registry.suite_count - 1];
        *suite = (TestSuite){test_case->suite_name, NULL, 0, NULL};
    }

    // Add test to suite
    suite->test_count++;
    suite->tests =
        (TestCase *)realloc(suite->tests, suite->test_count * sizeof(TestCase));
    suite->tests[suite->test_count - 1] = *test_case;
}

// test runner
static int RUN_ALL_TESTS(void) {
    printf("[==========] Running %zu test suites\n", test_registry.suite_count);

    size_t total_tests = 0;
    size_t total_passed = 0;
    size_t total_failed = 0;
    size_t total_skipped = 0;
    size_t total_errors = 0;

    for (size_t i = 0; i < test_registry.suite_count; i++) {
        TestSuite *suite = &test_registry.suites[i];
        printf(
            "[----------] %zu tests from %s\n", suite->test_count, suite->name);

        size_t suite_passed = 0;
        size_t suite_failed = 0;
        size_t suite_skipped = 0;
        size_t suite_errors = 0;

        for (size_t j = 0; j < suite->test_count; j++) {
            TestCase *test = &suite->tests[j];
            printf("[ RUN      ] %s.%s\n", suite->name, test->name);

            TestResult result = test->function();

            switch (result) {
            case TEST_PASS:
                printf("[       OK ] %s.%s\n", suite->name, test->name);
                suite_passed++;
                break;
            case TEST_FAIL:
                printf("[  FAILED  ] %s.%s\n", suite->name, test->name);
                suite_failed++;
                break;
            case TEST_SKIP:
                printf("[  SKIPPED ] %s.%s\n", suite->name, test->name);
                suite_skipped++;
                break;
            case TEST_ERROR:
                printf("[  ERROR   ] %s.%s\n", suite->name, test->name);
                suite_errors++;
                break;
            }
        }

        printf("[----------] %zu tests from %s (%d ms total)\n\n",
               suite->test_count,
               suite->name,
               0); // Time tracking can be added

        total_tests += suite->test_count;
        total_passed += suite_passed;
        total_failed += suite_failed;
        total_skipped += suite_skipped;
        total_errors += suite_errors;
    }

    printf("[==========] %zu tests from %zu test suites ran.\n",
           total_tests,
           test_registry.suite_count);
    printf("[  PASSED  ] %zu tests.\n", total_passed);
    if (total_failed > 0) {
        printf("[  FAILED  ] %zu tests.\n", total_failed);
    }
    if (total_skipped > 0) {
        printf("[  SKIPPED ] %zu tests.\n", total_skipped);
    }
    if (total_errors > 0) {
        printf("[  ERRORS  ] %zu tests.\n", total_errors);
    }

    return (total_failed == 0 && total_errors == 0) ? EXIT_SUCCESS
                                                    : EXIT_FAILURE;
}

#endif // !__NUTEST_H__
