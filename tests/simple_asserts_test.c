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

ACU_CONTEXT();

int main()
{
  ACU_RUN_TEST(test_integers_are_equal);
  ACU_RUN_TEST(test_strings_are_not_equal);
  ACU_SUMMARY();
}
