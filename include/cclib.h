#ifndef CCLIB_H
#define CCLIB_H

#include <limits.h>
#include <errno.h>
#include <stdio.h>

typedef struct {
  int result;
  int error;
} Sum;

typedef struct {
  char *string;
  int error;
} String;

__THROW __attribute_warn_unused_result__ int get_sum(const int *_arr,
                                                     const size_t _size);

__THROW __attribute_warn_unused_result__ int println(const char *_str);

__THROW __attribute_warn_unused_result__ String str_join(const char *_str1,
                                                         const char *_str2,
                                                         const char _delimiter);

__THROW
int free_all(const size_t _num, ...);

#endif
