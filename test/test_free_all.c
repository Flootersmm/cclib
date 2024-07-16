#include "test_util.h"

void test_free_all() {
  printf("test_free_all(): Beginning tests.\n");
  char *ptr1 = malloc(10 * sizeof(char));
  int *ptr2 = malloc(5 * sizeof(int));
  double *ptr3 = malloc(3 * sizeof(double));
  assert(ptr1 != NULL && ptr2 != NULL && ptr3 != NULL);

  free_all(3, &ptr1, &ptr2, &ptr3);
  assert(ptr1 == NULL);
  assert(ptr2 == NULL);
  assert(ptr3 == NULL);

  ptr1 = NULL;
  ptr2 = NULL;
  ptr3 = NULL;

  free_all(3, &ptr1, &ptr2, &ptr3);
  assert(ptr1 == NULL);
  assert(ptr2 == NULL);
  assert(ptr3 == NULL);

  ptr1 = malloc(10 * sizeof(char));
  ptr2 = NULL;
  ptr3 = malloc(3 * sizeof(double));
  assert(ptr1 != NULL && ptr3 != NULL);

  free_all(3, &ptr1, &ptr2, &ptr3);
  assert(ptr1 == NULL);
  assert(ptr2 == NULL);
  assert(ptr3 == NULL);

  printf("test_free_all(): All tests passed.\n");
}
