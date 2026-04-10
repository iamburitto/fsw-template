#include <stdio.h>
#include <stdint.h>
#include "packet.h"

static int test_valid_packet(void)
{
    uint8_t buf[] = {0xAA, 3, 1, 2, 3};
    packet_t pkt;
    size_t consumed = 0;

    int result = packet_parse(buf, sizeof(buf), &pkt, &consumed);

    if (result != 1) return 1;
    if (pkt.length != 3) return 1;
    if (consumed != 5) return 1;

    return 0;
}

int main(void)
{
    int failures = 0;

    failures += test_valid_packet();

    if (failures == 0)
    {
        printf("PASS\n");
        return 0;
    }

    printf("FAIL\n");
    return 1;
}
