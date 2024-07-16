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

int get_sum(const int *arr, const size_t size);
int println(const char *str);
String str_join(const char *str1, const char *str2, const char delimiter);
int free_all(const size_t num, ...);

#endif
