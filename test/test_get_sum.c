#include "test_util.h"

void test_get_sum() {
  printf("test_get_sum(): Beginning tests.\n");
  int sum;

  int arr1[4] = {1, 2, 3, 4};
  sum = get_sum(arr1, 4);
  assert(sum == 10);

  int arr2[1] = {5};
  sum = get_sum(arr2, 1);
  assert(sum == 5);

  int arr3[4] = {-1, -2, -3, -4};
  sum = get_sum(arr3, 4);
  assert(sum == -10);

  int arr4[4] = {1, -1, 2, -2};
  sum = get_sum(arr4, 4);
  assert(sum == 0);

  int arr5[4] = {0, 0, 0, 0};
  sum = get_sum(arr5, 4);
  assert(sum == 0);

  int arr7[2] = {INT_MAX, 1};
  errno = 0;
  sum = get_sum(arr7, 2);
  assert(errno == ERANGE);

  int arr8[2] = {INT_MIN, -1};
  errno = 0;
  sum = get_sum(arr8, 2);
  assert(errno == ERANGE);

  int arr9[2] = {INT_MAX, INT_MAX};
  errno = 0;
  sum = get_sum(arr9, 2);
  assert(errno == ERANGE);

  int arr10[2] = {INT_MIN, INT_MIN};
  errno = 0;
  sum = get_sum(arr10, 2);
  assert(errno == ERANGE);

  int arr11[4] = {INT_MAX, -1, INT_MAX, -1};
  sum = get_sum(arr11, 4);
  assert(errno == ERANGE);

  int arr12[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  sum = get_sum(arr12, 10);
  assert(sum == 10);

  int arr13[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  sum = get_sum(arr13, 10);
  assert(sum == -10);

  printf("test_get_sum(): All tests passed.\n");
}
