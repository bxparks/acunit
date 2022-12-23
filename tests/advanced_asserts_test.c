#include <acunit.h>

//-----------------------------------------------------------------------------

ACU_TEST(test_assert_with_message)
{
  int a = 1;
  int b = 1;
  ACU_ASSERT_MSG(a == b, "a and b are different");
}

//-----------------------------------------------------------------------------

// If the ACU_ASSERT() macro is refactored into a sub-function, the acu_context
// object must be passed in manually from the calling test function.
static void check_some_condition(AcuContext *acu_context) {
  int a = 1;
  int b = 1;
  int c = 2;
  ACU_ASSERT(a == b);
  ACU_ASSERT(a != c);
}

ACU_TEST(test_assert_no_fatal_failure)
{
  ACU_ASSERT_NO_FATAL_FAILURE(check_some_condition(acu_context));
}

//-----------------------------------------------------------------------------

ACU_CONTEXT();

int main()
{
  ACU_RUN_TEST(test_assert_with_message);
  ACU_RUN_TEST(test_assert_no_fatal_failure);
  ACU_SUMMARY();
}
