### NuTest - A Lightweight Unit Testing Framework for C

- ***Installation***
```
curl -O https://raw.githubusercontent.com/ridwanalmahmud/nutest/refs/heads/master/nutest.h"
```

- ***Core Macros***

| Macro | Description |
|-------|-------------|
| `TEST(suite, name)` | Defines a test case |
| `TEST_F_DESC(suite, name, desc)` | Defines a test case with description |
| `ASSERT_TRUE(cond)` | Fails if condition is false |
| `ASSERT_FALSE(cond)` | Fails if condition is true |
| `ASSERT_EQ(val1, val2)` | Fails if val1 ≠ val2 (int/pointer) |
| `ASSERT_NE(val1, val2)` | Fails if val1 = val2 |
| `ASSERT_GT(val1, val2)` | Fails if val1 <= val2 |
| `ASSERT_LT(val1, val2)` | Fails if val1 >= val2 |
| `ASSERT_GE(val1, val2)` | Fails if val1 < val2 |
| `ASSERT_LE(val1, val2)` | Fails if val1 > val2 |
| `ASSERT_FLOAT_EQ(val1, val2)` | Fails if floats not equal (with epsilon tolerance) |
| `ASSERT_DOUBLE_EQ(val1, val2)` | Fails if doubles not equal (with epsilon tolerance) |
| `ASSERT_NEAR(val1, val2, tol)` | Fails if val1 not within tolerance of val2 |
| `ASSERT_STREQ(str1, str2)` | Fails if str1 != str2 |
| `ASSERT_STRNE(str1, str2)` | Fails if str1 == str2 |
| `ASSERT_NULL(ptr)` | Fails if pointer is not NULL |
| `ASSERT_NOT_NULL(ptr)` | Fails if pointer is NULL |
| `ASSERT_MEM_EQ(a, b, size)` | Fails if memory differs for a & b |

- ***Benchmark Macros***

| Macro | Description |
|-------|-------------|
| `BENCHMARK_START(name)` | Starts timer (place at start of benchmark) |
| `BENCHMARK_END(name)` | Stops timer and prints duration |
| `BENCHMARK_FUNCTION(func, name, iterations)` | Runs benchmark on a function |

- ***Special Functions***

| Function | Description |
|----------|-------------|
| `RUN_ALL_TESTS()` | Runs all registered tests (returns 0 if all pass) |
| `SKIP_TEST()` | Immediately skips current test |

