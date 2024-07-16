#include "test_util.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_println(void) {
  printf("test_println(): Beginning tests.\n");

  FILE *output = fopen("tmp_output", "w+");
  assert(output != NULL);

  char *test_strings[] = {
      "Hello, World", "", "\n",
      "This is a very long string to test the println function to ensure it "
      "can handle long inputs correctly."};

  for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
    FILE *saved_stdout = stdout;
    stdout = freopen("tmp_output", "w+", stdout);
    assert(stdout != NULL);

    int result = println(test_strings[i]);
    assert(result == 0);

    fflush(stdout);
    stdout = saved_stdout;
    freopen("/dev/tty", "w", stdout);

    char buf[512] = {0};
    rewind(output);
    fread(buf, 1, strlen(test_strings[i]) + 2, output);
    buf[strlen(test_strings[i]) + 2] =
        '\0'; // +2 for the newline character added by println and null
              // terminator

    char expected_output[512];
    snprintf(expected_output, sizeof(expected_output), "%s\n", test_strings[i]);

    assert(strcmp(buf, expected_output) == 0);
  }

  fclose(output);
  remove("tmp_output");

  printf("test_println(): All tests passed.\n");
}
