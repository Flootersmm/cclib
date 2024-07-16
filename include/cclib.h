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

int get_sum(int *arr, int size);
int println(char *str);
String str_join(const char *str1, const char *str2, const char delimiter);
int free_all(int num, ...);

#endif
