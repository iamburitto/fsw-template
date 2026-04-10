#include "packet.h"

#define SYNC_BYTE 0xAA

int packet_parse(const uint8_t *buffer, size_t buffer_len, packet_t *out, size_t *consumed)
{
    if (buffer_len < 3)
        return 0;

    if (buffer[0] != SYNC_BYTE)
    {
        *consumed = 1;
        return -1;
    }

    uint16_t length = buffer[1];

    if (length > PACKET_MAX_PAYLOAD)
    {
        *consumed = 1;
        return -1;
    }

    if (buffer_len < (size_t)(2 + length))
        return 0;

    for (uint16_t i = 0; i < length; i++)
        out->payload[i] = buffer[2 + i];

    out->length = length;
    *consumed = 2 + length;

    return 1;
}
