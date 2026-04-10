#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include <stddef.h>

#define PACKET_MAX_PAYLOAD 256

typedef struct
{
    uint8_t payload[PACKET_MAX_PAYLOAD];
    uint16_t length;
} packet_t;

int packet_parse(const uint8_t *buffer, size_t buffer_len, packet_t *out, size_t *consumed);

#endif
