#include <acunit.h>

ACU_TEST(test_assert_with_message)
{
  int a = 1;
  int b = 1;
  ACU_ASSERT_MSG(a == b, "a and b are different");
}

/***************************************************************/

ACU_VARS();

int main()
{
  ACU_RUN_TEST(test_assert_with_message);
  ACU_SUMMARY();
}
