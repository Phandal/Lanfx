#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1000

typedef struct __attribute__((__packed__)) {
  uint16_t size;
  uint16_t protocol : 12;
  uint8_t addressable : 1;
  uint8_t tagged : 1;
  uint8_t reserved_1 : 2;
  uint32_t source;

  uint64_t target;
  uint8_t reserved_2[6];
  uint8_t res_required : 1;
  uint8_t ack_required : 1;
  uint8_t reserved_3 : 6;
  uint8_t sequence;

  uint64_t reserved_4;
  uint16_t pkt_type;
  uint16_t reserved_5;
} lx_frame_t;

int get_line(char* line, int limit);
int decode_frame(lx_frame_t* f, const char* hex);
void decode_target(lx_frame_t* f, char* target);
void print_frame(lx_frame_t* f, char* target);

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

int decode_frame(lx_frame_t* f, const char* hex) {
  int len = strlen(hex);

  if (len < 72) {
    fprintf(stderr, "Hex Data is too short to be a valid frame.");
    return 0;
  }

  uint8_t buffer[36] = {};

  for (int i = 0; i < len/ 2 && i < 36; ++i) {
    unsigned int nxt;
    sscanf(hex + (2 * i), "%02x", &nxt);
    buffer[i] = (uint8_t)nxt;
  }

  memcpy(f, buffer, 36);
  
  return 1;
}

void decode_target(lx_frame_t* f, char* target) {
  char ss[16] = {};
  sprintf(ss, "%#06lx", f->target);

  for (int i = 12; i > 0; i -= 2) {
    target[12 - i] = ss[i];
    target[13 - i] = ss[i + 1];
  }

  target[13] = '\0';
}

void print_frame(lx_frame_t* f, char* target) {
  printf("Size: %d\n", f->size);
  printf("Protocol: %d\n", f->protocol);
  printf("Addressable: %d\n", f->addressable);
  printf("Tagged: %d\n", f->tagged);
  printf("Source: %d\n", f->source);
  printf("Target: %s\n", target);
  printf("Response Required: %d\n", f->res_required);
  printf("Acknowledge Required: %d\n", f->ack_required);
  printf("Sequence: %d\n", f->sequence);
  printf("Packet Type: %d\n", f->pkt_type);
}
