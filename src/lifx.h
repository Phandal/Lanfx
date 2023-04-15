#ifndef _LIFX_H_
#define _LIFX_H_

#include <stdint.h>

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

int decode_frame(lx_frame_t* f, const char* hex);

void decode_target(lx_frame_t* f, char* target);

void print_frame(lx_frame_t* f, char* target);

#endif // __LIFX_H_
