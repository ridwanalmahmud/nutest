#ifndef __NUTEST_H__
#define __NUTEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <float.h>
#include <math.h>

// ANSI color codes
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"
#define COLOR_BOLD "\033[1m"

// Test result codes
typedef enum { TEST_PASS, TEST_FAIL, TEST_SKIP, TEST_ERROR } TestResult;

// Test case function type
typedef TestResult (*TestFunc)(void);

// Test case structure
typedef struct {
    const char *name;
    TestFunc function;
    const char *suite_name;
    const char *description;
} TestCase;

// Test suite structure
typedef struct {
    const char *name;
    TestCase *tests;
    size_t test_count;
    const char *description;
} TestSuite;

// Test registry
typedef struct {
    TestSuite *suites;
    size_t suite_count;
} TestRegistry;

// Global test registry
static TestRegistry test_registry = {NULL, 0};

#define ASSERT_TRUE(condition)                                       \
    do {                                                             \
        if (!(condition)) {                                          \
            fprintf(stderr,                                          \
                    "[ " COLOR_RED "FAIL" COLOR_RESET                \
                    "    ] %s:%d: Expected: %s evaluates to true\n", \
                    __FILE__,                                        \
                    __LINE__,                                        \
                    #condition);                                     \
            return TEST_FAIL;                                        \
        }                                                            \
    } while (0)

#define ASSERT_FALSE(condition)                                       \
    do {                                                              \
        if (condition) {                                              \
            fprintf(stderr,                                           \
                    "[ " COLOR_RED "FAIL" COLOR_RESET                 \
                    "    ] %s:%d: Expected: %s evaluates to false\n", \
                    __FILE__,                                         \
                    __LINE__,                                         \
                    #condition);                                      \
            return TEST_FAIL;                                         \
        }                                                             \
    } while (0)

#define ASSERT_EQ(expected, actual)                                 \
    do {                                                            \
        if ((expected) != (actual)) {                               \
            fprintf(stderr,                                         \
                    "[ " COLOR_RED "FAIL" COLOR_RESET               \
                    "    ] %s:%d: Expected: %s == %s (%g vs %g)\n", \
                    __FILE__,                                       \
                    __LINE__,                                       \
                    #expected,                                      \
                    #actual,                                        \
                    (double)(expected),                             \
                    (double)(actual));                              \
            return TEST_FAIL;                                       \
        }                                                           \
    } while (0)

#define ASSERT_NE(val1, val2)                                          \
    do {                                                               \
        if ((val1) == (val2)) {                                        \
            fprintf(stderr,                                            \
                    "[ " COLOR_RED "FAIL" COLOR_RESET                  \
                    "    ] %s:%d: Expected: %s != %s (both are %g)\n", \
                    __FILE__,                                          \
                    __LINE__,                                          \
                    #val1,                                             \
                    #val2,                                             \
                    (double)(val1));                                   \
            return TEST_FAIL;                                          \
        }                                                              \
    } while (0)

#define ASSERT_GT(val1, val2)                                      \
    do {                                                           \
        if ((val1) <= (val2)) {                                    \
            fprintf(stderr,                                        \
                    "[ " COLOR_RED "FAIL" COLOR_RESET              \
                    "    ] %s:%d: Expected: %s > %s (%g vs %g)\n", \
                    __FILE__,                                      \
                    __LINE__,                                      \
                    #val1,                                         \
                    #val2,                                         \
                    (double)(val1),                                \
                    (double)(val2));                               \
            return TEST_FAIL;                                      \
        }                                                          \
    } while (0)

#define ASSERT_LT(val1, val2)                                      \
    do {                                                           \
        if ((val1) >= (val2)) {                                    \
            fprintf(stderr,                                        \
                    "[ " COLOR_RED "FAIL" COLOR_RESET              \
                    "    ] %s:%d: Expected: %s < %s (%g vs %g)\n", \
                    __FILE__,                                      \
                    __LINE__,                                      \
                    #val1,                                         \
                    #val2,                                         \
                    (double)(val1),                                \
                    (double)(val2));                               \
            return TEST_FAIL;                                      \
        }                                                          \
    } while (0)

#define ASSERT_GE(val1, val2)                                       \
    do {                                                            \
        if ((val1) < (val2)) {                                      \
            fprintf(stderr,                                         \
                    "[ " COLOR_RED "FAIL" COLOR_RESET               \
                    "    ] %s:%d: Expected: %s >= %s (%g vs %g)\n", \
                    __FILE__,                                       \
                    __LINE__,                                       \
                    #val1,                                          \
                    #val2,                                          \
                    (double)(val1),                                 \
                    (double)(val2));                                \
            return TEST_FAIL;                                       \
        }                                                           \
    } while (0)

#define ASSERT_LE(val1, val2)                                       \
    do {                                                            \
        if ((val1) > (val2)) {                                      \
            fprintf(stderr,                                         \
                    "[ " COLOR_RED "FAIL" COLOR_RESET               \
                    "    ] %s:%d: Expected: %s <= %s (%g vs %g)\n", \
                    __FILE__,                                       \
                    __LINE__,                                       \
                    #val1,                                          \
                    #val2,                                          \
                    (double)(val1),                                 \
                    (double)(val2));                                \
            return TEST_FAIL;                                       \
        }                                                           \
    } while (0)

#define ASSERT_FLOAT_EQ(val1, val2)                               \
    do {                                                          \
        float _val1 = (val1);                                     \
        float _val2 = (val2);                                     \
        float _diff = fabsf(_val1 - _val2);                       \
        if (_diff > FLT_EPSILON) {                                \
            fprintf(stderr,                                       \
                    "[ " COLOR_RED "FAIL" COLOR_RESET             \
                    "    ] %s:%d: val1: %s == %s (%.9g vs %.9g, " \
                    "diff %.9g)\n",                               \
                    __FILE__,                                     \
                    __LINE__,                                     \
                    #val1,                                        \
                    #val2,                                        \
                    _val1,                                        \
                    _val2,                                        \
                    _diff);                                       \
            return TEST_FAIL;                                     \
        }                                                         \
    } while (0)

#define ASSERT_DOUBLE_EQ(val1, val2)                                \
    do {                                                            \
        double _val1 = (val1);                                      \
        double _val2 = (val2);                                      \
        double _diff = fabs(_val1 - _val2);                         \
        if (_diff > DBL_EPSILON) {                                  \
            fprintf(stderr,                                         \
                    "[ " COLOR_RED "FAIL" COLOR_RESET               \
                    "    ] %s:%d: val1: %s == %s (%.17g vs %.17g, " \
                    "diff %.17g)\n",                                \
                    __FILE__,                                       \
                    __LINE__,                                       \
                    #val1,                                          \
                    #val2,                                          \
                    _val1,                                          \
                    _val2,                                          \
                    _diff);                                         \
            return TEST_FAIL;                                       \
        }                                                           \
    } while (0)

#define ASSERT_NEAR(val1, val2, tolerance)                          \
    do {                                                            \
        double _val1 = (val1);                                      \
        double _val2 = (val2);                                      \
        double _diff = fabs(_val1 - _val2);                         \
        if (_diff > (tolerance)) {                                  \
            fprintf(stderr,                                         \
                    "[ " COLOR_RED "FAIL" COLOR_RESET               \
                    "    ] %s:%d: val1: %s ~= %s (%.17g vs %.17g, " \
                    "diff %.17g > tol %.17g)\n",                    \
                    __FILE__,                                       \
                    __LINE__,                                       \
                    #val1,                                          \
                    #val2,                                          \
                    _val1,                                          \
                    _val2,                                          \
                    _diff,                                          \
                    (tolerance));                                   \
            return TEST_FAIL;                                       \
        }                                                           \
    } while (0)

#define ASSERT_STREQ(str1, str2)                            \
    do {                                                    \
        const char *_str1 = (str1);                         \
        const char *_str2 = (str2);                         \
        if (strcmp(_str1, _str2) != 0) {                    \
            fprintf(stderr,                                 \
                    "[ " COLOR_RED "FAIL" COLOR_RESET       \
                    "    ] %s:%d: Expected: %s == %s\n"     \
                    "                  \"%s\" vs \"%s\"\n", \
                    __FILE__,                               \
                    __LINE__,                               \
                    #str1,                                  \
                    #str2,                                  \
                    _str1,                                  \
                    _str2);                                 \
            return TEST_FAIL;                               \
        }                                                   \
    } while (0)

#define ASSERT_STRNE(str1, str2)                                \
    do {                                                        \
        const char *_str1 = (str1);                             \
        const char *_str2 = (str2);                             \
        if (strcmp(_str1, _str2) == 0) {                        \
            fprintf(stderr,                                     \
                    "[ " COLOR_RED "FAIL" COLOR_RESET           \
                    "    ] %s:%d: Expected: %s != %s\n"         \
                    "                  Both equal to \"%s\"\n", \
                    __FILE__,                                   \
                    __LINE__,                                   \
                    #str1,                                      \
                    #str2,                                      \
                    _str1);                                     \
            return TEST_FAIL;                                   \
        }                                                       \
    } while (0)

#define ASSERT_NULL(ptr)                                  \
    do {                                                  \
        if (ptr != NULL) {                                \
            fprintf(stderr,                               \
                    "[ " COLOR_RED "FAIL" COLOR_RESET     \
                    "    ] %s:%d: %s is not NULL (%p)\n", \
                    __FILE__,                             \
                    __LINE__,                             \
                    #ptr,                                 \
                    (void *)(ptr));                       \
            return TEST_FAIL;                             \
        }                                                 \
    } while (0)

#define ASSERT_NOT_NULL(ptr)                          \
    do {                                              \
        if (ptr == NULL) {                            \
            fprintf(stderr,                           \
                    "[ " COLOR_RED "FAIL" COLOR_RESET \
                    "    ] %s:%d: %s is NULL\n",      \
                    __FILE__,                         \
                    __LINE__,                         \
                    #ptr);                            \
            return TEST_FAIL;                         \
        }                                             \
    } while (0)

#define ASSERT_MEM_EQ(expected, actual, size)                      \
    do {                                                           \
        if (memcmp((expected), (actual), (size))) {                \
            fprintf(stderr,                                        \
                    "[ " COLOR_RED "FAIL" COLOR_RESET              \
                    "    ] %s:%d: Memory differs for %s and %s\n", \
                    __FILE__,                                      \
                    __LINE__,                                      \
                    #expected,                                     \
                    #actual);                                      \
            return TEST_FAIL;                                      \
        }                                                          \
    } while (0)

// Test registration macros
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

// Skip test macro
#define SKIP() return TEST_SKIP

// Benchmarking macros
#define BENCHMARK_START(name)                               \
    struct timespec _bench_start_##name, _bench_end_##name; \
    clock_gettime(CLOCK_MONOTONIC, &_bench_start_##name)

#define BENCHMARK_END(name)                                               \
    clock_gettime(CLOCK_MONOTONIC, &_bench_end_##name);                   \
    double _bench_time_##name =                                           \
        (_bench_end_##name.tv_sec - _bench_start_##name.tv_sec) +         \
        (_bench_end_##name.tv_nsec - _bench_start_##name.tv_nsec) / 1e9;  \
    printf("[ " COLOR_CYAN "BENCH" COLOR_RESET "   ] %s: %.9f seconds\n", \
           #name,                                                         \
           _bench_time_##name)

#define BENCHMARK_FUNCTION(func, name, iterations)           \
    do {                                                     \
        BENCHMARK_START(name);                               \
        for (int _iter = 0; _iter < (iterations); _iter++) { \
            func;                                            \
        }                                                    \
        BENCHMARK_END(name);                                 \
    } while (0)

// Test registration function
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

// Test runner
static int RUN_ALL_TESTS(void) {
    printf("[=========] Running %zu test suites\n", test_registry.suite_count);

    size_t total_tests = 0;
    size_t total_passed = 0;
    size_t total_failed = 0;
    size_t total_skipped = 0;
    size_t total_errors = 0;

    for (size_t i = 0; i < test_registry.suite_count; i++) {
        TestSuite *suite = &test_registry.suites[i];
        printf(
            "[---------] %zu tests from %s\n", suite->test_count, suite->name);

        size_t suite_passed = 0;
        size_t suite_failed = 0;
        size_t suite_skipped = 0;
        size_t suite_errors = 0;

        for (size_t j = 0; j < suite->test_count; j++) {
            TestCase *test = &suite->tests[j];
            printf("[ RUN     ] %s.%s\n", suite->name, test->name);

            TestResult result = test->function();

            switch (result) {
            case TEST_PASS:
                printf("[ " COLOR_GREEN "PASS" COLOR_RESET "    ] %s.%s\n",
                       suite->name,
                       test->name);
                suite_passed++;
                break;
            case TEST_FAIL:
                printf("[ " COLOR_RED "FAIL" COLOR_RESET "    ] %s.%s\n",
                       suite->name,
                       test->name);
                suite_failed++;
                break;
            case TEST_SKIP:
                printf("[ " COLOR_YELLOW "SKIP" COLOR_RESET "    ] %s.%s\n",
                       suite->name,
                       test->name);
                suite_skipped++;
                break;
            case TEST_ERROR:
                printf("[ " COLOR_MAGENTA "ERROR" COLOR_RESET "   ] %s.%s\n",
                       suite->name,
                       test->name);
                suite_errors++;
                break;
            }
        }

        printf("[---------] %zu tests from %s (%d ms total)\n\n",
               suite->test_count,
               suite->name,
               0);

        total_tests += suite->test_count;
        total_passed += suite_passed;
        total_failed += suite_failed;
        total_skipped += suite_skipped;
        total_errors += suite_errors;
    }

    printf("[=========] %zu tests from %zu test suites ran.\n",
           total_tests,
           test_registry.suite_count);

    if (total_passed > 0) {
        printf("[ " COLOR_GREEN "PASSED" COLOR_RESET "  ] %zu tests.\n",
               total_passed);
    }
    if (total_failed > 0) {
        printf("[ " COLOR_RED "FAILED" COLOR_RESET "  ] %zu tests.\n",
               total_failed);
    }
    if (total_skipped > 0) {
        printf("[ " COLOR_YELLOW "SKIPPED" COLOR_RESET " ] %zu tests.\n",
               total_skipped);
    }
    if (total_errors > 0) {
        printf("[ " COLOR_MAGENTA "ERRORS" COLOR_RESET "  ] %zu tests.\n",
               total_errors);
    }

    return (total_failed == 0 && total_errors == 0) ? EXIT_SUCCESS
                                                    : EXIT_FAILURE;
}

#endif // !__NUTEST_H__
