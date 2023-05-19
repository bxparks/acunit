/*
MIT License

Copyright (c) 2022 Brian T. Park

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @mainpage ACUnit Library
 *
 * This is the Doxygen documentation for the
 * <a href="https://github.com/bxparks/acunit">ACUnit Library</a>.
 *
 * Click on the "Classes" menu above to see the list of classes.
 *
 * Click on the "Files" menu above to see the list of header files.
 */

/**
 * @file acunit.h
 *
 * A minimal unit testing framework for the C language.
 *
 * Adapted from [minunit.h](https://jera.com/techinfo/jtns/jtn002) which has
 * the following license: "You may use the code in this tech note for any
 * purpose, with the understanding that it comes with NO WARRANTY."
 */

#include <stdio.h>

/**
 * A data struct passed into each test function and holds the result of the
 * test.
 *
 * It may be possible to extend ACUnit to support multiple threads. But I have
 * not spent any time researching this because my tests are small enough that I
 * don't need to use multiple threads.
 */
typedef struct AcuContext {
  /**
   * Holds the the pass (0) or fail (!=0) err code of a specific unit test. This
   * is set to 0 before calling each test.
   *
   * The alternative design is to return the err code as a return value of the
   * function (i.e. making ACU_TEST() define a function that returns an 'int').
   * But that forces each test function to terminate with a 'return 1'
   * statement. This return statement is very easy to forget, and it quickly
   * becomes annoying. Using the AcuContext object to return the err code solves
   * that usuability problem.
   */
  int err;

  /** Number of unit tests that were executed. */
  int executed_count;

  /** Number of unit tests that failed. */
  int failed_count;
} AcuContext;

/** Define the context required by ACUnit. */
#define ACU_CONTEXT() AcuContext acu_context = {0, 0, 0}

/**
 * Define a test function that sets the acu_context.err to 1 on failure, 0 on
 * success.
 */
#define ACU_TEST(name) void name(AcuContext *acu_context)

/**
 * Print assertion failure message. The format is compatible with the error
 * messages printed out by the C compiler. This format is recognized by editors
 * such as vim to quickly jump to the location of the error in the source file.
 *
 * It looks like the value of the `__LINE__` macro is guaranteed to fit inside a
 * `long` in C11 (https://stackoverflow.com/questions/5075928).
 */
extern inline void acu_assertion(
  AcuContext *acu_context,
  const char *file,
  long line,
  const char *condition,
  const char *message)
{
  printf("%s:%ld: Assertion failed: [%s] is false", file, line, condition);
  acu_context->failed_count++;
  if (message) {
    printf(": %s\n", message);
  } else {
    printf("\n");
  }
}

/** Implement the 1-argument ACU_ASSERT() macro. */
#define ACU_ASSERT(condition) \
  do { \
    if (!(condition)) { \
      acu_assertion(acu_context, __FILE__, __LINE__, #condition, NULL); \
      acu_context->err = 1; \
      return; \
    } \
  } while (0)

/**
 * Implement the 2-argument ACU_ASSERT() macro with a message. If we try to use
 * a CPP trick (https://stackoverflow.com/questions/11761703) to overload
 * ACU_ASSERT() to take 1 or 2 arguments, we get a GCC error message saying that
 * 'ISO C99 requires at least one argument for the "..." in a variadic macro'.
 */
#define ACU_ASSERT_MSG(condition, message) \
  do { \
    if (!(condition)) { \
      acu_assertion(acu_context, __FILE__, __LINE__, #condition, message); \
      acu_context->err = 1; \
      return; \
    } \
  } while (0)

/**
 * Run the given 'test' function. If an assertion fails, print the diagnostic
 * message that was returned.
 */
#define ACU_RUN_TEST(test) \
  do { \
    acu_context.err = 0; \
    test(&acu_context); \
    acu_context.executed_count++; \
    printf("%s: %s\n", (acu_context.err ? "FAILED" : "PASSED"), #test); \
  } while (0)

/**
 * Print out the test summary. Returns 1 if any test failed, which causes the
 * `main()` function to return a non-zero exit code to indicate failure.
 */
#define ACU_SUMMARY() \
  do { \
    if (acu_context.failed_count) { \
      printf("Summary: FAILED: %d failed out of %d test(s)\n", \
          acu_context.failed_count, acu_context.executed_count); \
    } else { \
      printf("Summary: PASSED: %d tests(s)\n", acu_context.executed_count); \
    } \
    return acu_context.failed_count != 0; \
  } while (0)

/** Execute the `assertion` function, and return if the assertion failed. */
#define ACU_ASSERT_NO_FATAL_FAILURE(assertion) \
  do { \
    assertion; \
    if (acu_context->err) return; \
  } while (0)
