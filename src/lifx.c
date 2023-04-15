#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "lifx.h"

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
