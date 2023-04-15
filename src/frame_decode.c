#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lifx.h"

#define MAX_LINE 1000

int get_line(char* line, int limit);

int main(void) {
  lx_frame_t* frame = (lx_frame_t*)malloc(sizeof(lx_frame_t));
  char hex[MAX_LINE];
  char target[13];
  int len;
  int counter = 1;

  while ((len = get_line(hex, MAX_LINE)) > 1) {
    decode_frame(frame, hex);
    if (!decode_frame(frame, hex)) {
      fprintf(stderr, "Could not read frame.\n");
      free(frame);
      return EXIT_FAILURE;
    }

    decode_target(frame, target);
    printf("Frame for Response: %d\n", counter);
    print_frame(frame, target);
    putchar('\n');
    ++counter;
  }
  free(frame);

  return EXIT_SUCCESS;
}

int get_line(char* s, int limit) {
  int c, i = 0;
  while (i < limit-1 && (c = getchar()) != '\n' && c != EOF) {
    s[i++] = c;
  }

  s[i] = '\0';
  return i;
}

