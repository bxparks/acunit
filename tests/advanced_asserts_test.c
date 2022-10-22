#include <acunit.h>

//-----------------------------------------------------------------------------

ACU_TEST(test_assert_with_message)
{
  int a = 1;
  int b = 1;
  ACU_ASSERT_MSG(a == b, "a and b are different");
}

//-----------------------------------------------------------------------------

static void check_some_condition() {
  int a = 1;
  int b = 1;
  int c = 2;
  ACU_ASSERT(a == b);
  ACU_ASSERT(a != c);
}

ACU_TEST(test_assert_no_fatal_failure)
{
  ACU_ASSERT_NO_FATAL_FAILURE(check_some_condition());
}

//-----------------------------------------------------------------------------

ACU_VARS();

int main()
{
  ACU_RUN_TEST(test_assert_with_message);
  ACU_RUN_TEST(test_assert_no_fatal_failure);
  ACU_SUMMARY();
}
