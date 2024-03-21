#include "bitreader.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitReader *bit_read_open(const char *filename) {
    BitReader *br = (BitReader *) calloc(sizeof(BitReader), 1);
    if (br == NULL) {
        return NULL;
    }
    br->underlying_stream = fopen(filename, "rb");
    if (br->underlying_stream == NULL) {
        free(br);
        return NULL;
    }
    br->byte = 0;
    br->bit_position = 8;
    return br;
}

void bit_read_close(BitReader **pbuf) {
    if (*pbuf != NULL) {
        fclose((*pbuf)->underlying_stream);
        free(*pbuf);
        *pbuf = NULL;
    } else {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
}

uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        buf->byte = (uint8_t) fgetc(buf->underlying_stream);
        buf->bit_position = 0;
    }
    uint8_t bit = (buf->byte >> buf->bit_position) & 1;
    buf->bit_position += 1;
    return bit;
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0x00;
    for (int i = 0; i < 8; i++) {
        uint8_t b = bit_read_bit(buf);
        byte |= (b << i);
    }
    return byte;
}

uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t word = 0x0000;
    for (int i = 0; i < 16; i++) {
        uint16_t b = bit_read_bit(buf);
        word |= (b << i);
    }
    return word;
}

uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t word = 0x00000000;
    for (int i = 0; i < 32; i++) {
        uint32_t b = bit_read_bit(buf);
        word |= (b << i);
    }
    return word;
}
