# ACUnit

A simple C unit testing framework for the C language (C99 and later) inspired by
[MinUnit](http://www.jera.com/techinfo/jtns/jtn002.html) and
[AUnit](https://github.com/bxparks/AUnit). The library consists of only a single
header file `acunit.h` which defines 6 macros. Normally only 5 will be used in a
unit test program:

* `ACU_TEST(name)`
* `ACU_ASSERT(boolean_expression)`
* `ACU_VARS()`
* `ACU_RUN_TEST(name)`
* `ACU_SUMMARY()`

**Version**: 0.0.0 (2022-08-22)

**Changelog**: [CHANGELOG.md](CHANGELOG.md)

## Table of Contents

* [Hello ACUnit](#HelloACUnit)
* [Installation](#Installation)
* [Usage](#Usage)
* [Examples](#Examples)
* [System Requirements](#SystemRequirements)
* [Motivation](#Motivation)
* [License](#License)
* [Feedback and Support](#FeedbackAndSupport)
* [Authors](#Authors)

<a name="HelloACUnit"></a>
## Hello ACUnit

```C
#include <acunit.h>
#include <string.h>

ACU_TEST(test_integers_are_equal)
{
  int x = 3;
  int y = 3;
  ACU_ASSERT(x == y);
}

ACU_TEST(test_strings_are_not_equal)
{
  const char s[] = "abc";
  const char t[] = "def";
  ACU_ASSERT(strcmp(s, t) != 0);
}

//-----------------------------------------------------------------------------

ACU_VARS();

int main()
{
  ACU_RUN_TEST(test_integers_are_equal);
  ACU_RUN_TEST(test_strings_are_not_equal);
  ACU_SUMMARY();
}
```

<a name="Installation"></a>
## Installation

Clone this library from GitHub. The `master` branch contains the stable
releases. The `develop` branch contains the current development.

The library consists of only a single header file `acunit.h`. It can be copied
into the directory as needed. Or you can use the `-I` flag of the C compiler to
tell it where to find it.

<a name="Usage"></a>
## Usage

The unit test program must include the header file like this:

```C
#include <acunit.h>
```

There are 6 macros defined in the `acunit.h` file.

* `ACU_TEST(name)`
    * Defines a unit test function called `name`.
    * The macro should be followed by the body of the function enclosed in
      curly brace `{}`.
* `ACU_ASSERT(boolean_expression)`
    * Verifies that the expression is true.
    * If false, prints an error message and returns from the test function
      immediately.
    * The format of the error message is identical to the format used by the C
      compiler. This means that the error message can be parsed by text editors
      (like vim) to jump directly to the location of the assertion failure.
* `ACU_VARS()`
    * Defines the global variables needed by the framework.
    * Should be added just once in a test program, usually just before the
      `main()` function.
* `ACU_RUN_TEST(name)`
    * Runs the test function called `name`.
* `ACU_SUMMARY()`
    * Prints out a summary of the number of tests executed, and the number of
      tests that failed (if any).
    * Returns from the `main()` function with a non-zero status code if
      any test failed.
* `ACU_ASSERT_MSG(name, msg)`
    * A variant of `ACU_ASSERT()` that prints out `msg` if the assertion fails.
    * Useful for adding more context to the default error message.

The library assumes that a single `*.c` test file will be self-contained and
generates a single executable file (e.g. `*.out`). The `main()` function
must enumerate the test functions that will run using the `ACU_RUN_TEST()`
macro. If the test functions are spread across multiple `*.c` files, it becomes
too cumbersome to keep track of them.

<a name="Examples"></a>
## Examples

The `tests/` directory contains some simple tests to verify each of the macros
described above. It also contains a skeletal `Makefile` for the GNU Make program
that may be helpful if you are not already familiar with Make.

Assuming that you have GNU Make (`make`) and a C compiler (`cc`) installed, you
can type the following to compile and run the tests:

```
$ cd tests
$ make clean
$ make
$ make runtests
[...]
==== Running simple_asserts_test.out
PASSED: test_chars_are_equal
PASSED: test_integers_are_equal
PASSED: test_strings_are_not_equal
Summary: PASSED: 3 tests(s)
==== Running assert_with_message_test.out
PASSED: test_assert_with_message
Summary: PASSED: 1 tests(s)
```

If one of tests fail, then the output will look like:

```
==== Running simple_asserts_test.out
PASSED: test_chars_are_equal
simple_asserts_test.c:15: Assertion failed: [x == y] is false
FAILED: test_integers_are_equal
PASSED: test_strings_are_not_equal
Summary: FAILED: 1 failed out of 3 test(s)
```

<a name="SystemRequirements"></a>
## System Requirements

I am not an expert on the various versions of the C language. I think that the
use of an `extern inline` in `acunit.h` means that the C language must be C99 or
later.

I have tested this library on the following systems and compilers using the
`-std=c99` flag (which should compile with `-std=c11` as well):

* Ubuntu Linux 20.04 LTS
    * gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
    * clang version 10.0.0-4ubuntu1
    * GNU Make 4.2.1
* MacOS 11.6.8 (Big Sur)
    * Apple clang version 13.0.0 (clang-1300.0.29.30)
    * GNU Make 3.8.1

<a name="Motivation"></a>
## Motivation

There are several existing unit testing frameworks for the C language. But I
found most of them too complex for my needs.

* [Check](https://libcheck.github.io/check/)
* [AceUnit](http://aceunit.sourceforge.net/)
* [GNU Autounit](http://autounit.tigris.org/)
* [CUnit](http://cunit.sourceforge.net)
* [CuTest](http://cutest.sourceforge.net/)
* [CppUnit](http://cppunit.sourceforge.net/doc/cvs/index.html)
* [embUnit](http://sourceforge.net/projects/embunit/)
* [munit](https://nemequ.github.io/munit/)

The most promising library for my needs was
[MinUnit](http://www.jera.com/techinfo/jtns/jtn002.html). But the trouble was
that it was *too* simple, I needed a few extra features:

* An assertion error message that printed out the code that triggered
  the assertion, to help debugging.
* An assertion error message with the file name and line number of the
  assertion, in a format compatible with the `vim` editor for quick navigation.
* Helper macros (`ACU_TEST()`, `ACU_ASSERT()`, `ACU_RUN_TEST()`, `ACU_VARS()`,
  `ACU_SUMMARY()`) to reduce some of the boilerplate code.

Many of those macros were inspired by the
[AUnit](https://github.com/bxparks/AUnit) library that I created for the Arduino
programming environment. Adding those features resulted in this library.

<a name="License"></a>
## License

[MIT License](https://opensource.org/licenses/MIT)

<a name="FeedbackAndSupport"></a>
## Feedback and Support

If you have any questions, comments, or feature requests for this library,
please use the [GitHub
Discussions](https://github.com/bxparks/ACUnit/discussions) for this project. If
you have bug reports, please file a ticket in [GitHub
Issues](https://github.com/bxparks/ACUnit/issues). Feature requests should go
into Discussions first because they often have alternative solutions which are
useful to remain visible, instead of disappearing from the default view of the
Issue tracker after the ticket is closed.

Please refrain from emailing me directly unless the content is sensitive. The
problem with email is that I cannot reference the email conversation when other
people ask similar questions later.

<a name="Authors"></a>
## Authors

* Created by Brian T. Park (brian@xparks.net).
