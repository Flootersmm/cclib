#include "test_util.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void test_str_join() {
  printf("test_str_join(): Beginning tests.\n");

  String str1 = str_join("Hello", "world", ' ');
  assert(str1.error == 0);
  assert(strcmp(str1.string, "Hello world") == 0);
  free(str1.string);

  String str2 = str_join("Hello", "world", ',');
  assert(str2.error == 0);
  assert(strcmp(str2.string, "Hello,world") == 0);
  free(str2.string);

  String str3 = str_join("", "world", ' ');
  assert(str3.error == 0);
  assert(strcmp(str3.string, " world") == 0);
  free(str3.string);

  String str4 = str_join("Hello", "", ' ');
  assert(str4.error == 0);
  assert(strcmp(str4.string, "Hello ") == 0);
  free(str4.string);

  String str5 = str_join("", "", ' ');
  assert(str5.error == 0);
  assert(strcmp(str5.string, " ") == 0);
  free(str5.string);

  String str6 = str_join(NULL, "world", ' ');
  assert(str6.error == -1);
  assert(str6.string == NULL);

  String str7 = str_join("Hello", NULL, ' ');
  assert(str7.error == -1);
  assert(str7.string == NULL);

  String str8 = str_join(NULL, NULL, ' ');
  assert(str8.error == -1);
  assert(str8.string == NULL);

  printf("test_str_join(): All tests passed.\n");
}
