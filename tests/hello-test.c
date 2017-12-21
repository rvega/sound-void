#include <unity.h>

void test_hello(void) {
  TEST_ASSERT_EQUAL(1, 0);
}

int main(int argc, char *argv[]) {
  UNITY_BEGIN();  
  RUN_TEST(test_hello);
  return UNITY_END();
}
