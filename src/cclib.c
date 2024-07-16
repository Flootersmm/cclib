#include "../include/cclib.h"
#include <stddef.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

/// Add all member ints of an array.
///
/// Iterate through all values in an array of ints and add them together.
/// Checks for `NULL` array, size <= 0, and overflows, then sets errno
/// appropriately. Returns `INT_MIN` if errno gets set.
///
/// @param arr The array of ints to sum.
/// @param size The size of the array.
/// @return The sum of all ints in the array. `INT_MIN` if error.
int get_sum(int *arr, int size) {
  Sum sum;
  sum = (Sum){.result = 0, .error = 0};
  errno = 0;

  if (arr == NULL) {
    errno = EINVAL;
    perror("    get_sum() failed");
    return INT_MIN;
  }

  if (size <= 0) {
    errno = EINVAL;
    perror("    get_sum() failed");
    return INT_MIN;
  }

  for (int i = 0; i < size; i++) {
    if (arr[i] > 0 && sum.result > INT_MAX - arr[i]) {
      errno = ERANGE;
      perror("    get_sum() failed");
      return INT_MIN;
    }
    if (arr[i] < 0 && sum.result < INT_MIN - arr[i]) {
      errno = ERANGE;
      perror("    get_sum() failed");
      return INT_MIN;
    }

    sum.result += arr[i];
  }

  return sum.result;
}

/// Print string with linebreak
///
/// Prints a string with \n afterwards to create a new line and flush the
/// buffer.
///
/// @param str A string.
/// @return Result, 0 for success, -1 for failure.
int println(char *str) {
  errno = 0;
  if (str == NULL) {
    errno = EINVAL;
    perror("    println() failed");
    return -1;
  }

  printf("%s\n", str);
  return 0;
}

/// Join two strings with a delimiter
///
/// Utilises str_cpy to append two strings together, with a single character
/// delimiter between.
///
/// @param str1 The string before the delimiter.
/// @param str2 The string after the delimiter.
/// @param delimiter The single-character delimiter.
///
/// @return A `String`, containing `char * .string` and `int .error`.
String str_join(const char *str1, const char *str2, const char delimiter) {
  String new_str;
  new_str.error = 0;
  new_str.string = NULL;

  errno = 0;
  if (str1 == NULL || str2 == NULL) {
    errno = EINVAL;
    perror("    str_join() failed");
    new_str.error = -1;
    return new_str;
  }

  int len1 = strlen(str1);
  int len2 = strlen(str2);
  int new_size = len1 + len2 + 2;

  new_str.string = malloc(new_size);
  if (new_str.string == NULL) {
    perror("    malloc() failed");
    new_str.error = -1;
    return new_str;
  }

  strcpy(new_str.string, str1);
  new_str.string[len1] = delimiter;
  strcpy(new_str.string + len1 + 1, str2);

  return new_str;
}

/// Free all ptrs
///
/// Takes a variadic argument of ptrs and frees all of them.
///
/// @param num Number of variadic arguments.
/// @param ... Pointers to be freed.
///
/// @return 0 for success, -1 for failure.
int free_all(int num, ...) {
  va_list args;
  va_start(args, num);
  int error_occurred = 0;

  for (int i = 0; i < num; i++) {
    void **ptr = va_arg(args, void **);
    if (ptr != NULL && *ptr != NULL) {
      free(*ptr);
      *ptr = NULL;
    } else {
      error_occurred = 1;
      errno = EINVAL;
      perror("    free_all() failed");
    }
  }

  va_end(args);
  return error_occurred ? -1 : 0;
}
