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
/// appropriately. Returns `INT_MIN` if `errno` gets set.
///
/// @param _arr The array of ints to sum.
/// @param _size The size of the array.
/// @return The sum of all ints in the array. `INT_MIN` if error.
__THROW __attribute_warn_unused_result__ int get_sum(const int *_arr,
                                                     const size_t _size) {
  Sum _sum = {0, 0};
  errno = 0;

  if (_arr == NULL) {
    errno = EINVAL;
    perror("    get_sum() failed");
    return INT_MIN;
  }

  if (_size <= 0) {
    errno = EINVAL;
    perror("    get_sum() failed");
    return INT_MIN;
  }

  for (size_t _i = 0; _i < _size; _i++) {
    if (_arr[_i] > 0 && _sum.result > INT_MAX - _arr[_i]) {
      errno = ERANGE;
      perror("    get_sum() failed");
      return INT_MIN;
    }
    if (_arr[_i] < 0 && _sum.result < INT_MIN - _arr[_i]) {
      errno = ERANGE;
      perror("    get_sum() failed");
      return INT_MIN;
    }

    _sum.result += _arr[_i];
  }

  return _sum.result;
}

/// Print string with linebreak
///
/// Prints a string with `\n` afterwards to create a new line and flush the
/// buffer.
///
/// @param _str A string.
/// @return 0 for success, -1 for failure.
__THROW __attribute_warn_unused_result__ int println(const char *_str) {
  errno = 0;
  if (_str == NULL) {
    errno = EINVAL;
    perror("    println() failed");
    return -1;
  }

  printf("%s\n", _str);
  return 0;
}

/// Join two strings with a delimiter
///
/// Utilises str_cpy to append two strings together, with a single character
/// delimiter between.
///
/// @param _str1 The string before the delimiter.
/// @param _str2 The string after the delimiter.
/// @param _delimiter The single-character delimiter.
///
/// @return A `String`, containing `char * .string` and `int .error`.
__THROW __attribute_warn_unused_result__ String
str_join(const char *_str1, const char *_str2, const char _delimiter) {
  String _new_str = {NULL, 0};

  errno = 0;
  if (_str1 == NULL || _str2 == NULL) {
    errno = EINVAL;
    perror("    str_join() failed");
    _new_str.error = -1;
    return _new_str;
  }

  int _len1 = strlen(_str1);
  int _len2 = strlen(_str2);
  int _new_size = _len1 + _len2 + 2;

  _new_str.string = malloc(_new_size);
  if (_new_str.string == NULL) {
    perror("    malloc() failed");
    _new_str.error = -1;
    return _new_str;
  }

  strcpy(_new_str.string, _str1);
  _new_str.string[_len1] = _delimiter;
  strcpy(_new_str.string + _len1 + 1, _str2);

  return _new_str;
}

/// Free all ptrs
///
/// Takes a variadic argument of ptrs and frees all of them.
///
/// @param _num Number of variadic arguments.
/// @param ... Pointers to be freed.
///
/// @return 0 for success, -1 for failure.
__THROW
int free_all(const size_t _num, ...) {
  va_list _args;
  va_start(_args, _num);
  int _error_occurred = 0;

  for (size_t _i = 0; _i < _num; _i++) {
    void **_ptr = va_arg(_args, void **);
    if (_ptr != NULL && *_ptr != NULL) {
      free(*_ptr);
      *_ptr = NULL;
    } else {
      _error_occurred = 1;
      errno = EINVAL;
      perror("    free_all() failed");
    }
  }

  va_end(_args);
  return _error_occurred ? -1 : 0;
}
