#include "test_util.h"

int main() {
  test_get_sum();
  test_println();
  test_str_join();
  test_free_all();

  printf("\nAll tests passed!\n");
  return 0;
}
