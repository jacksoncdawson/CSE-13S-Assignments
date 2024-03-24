#include "bitwriter.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BitWriter {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    BitWriter *bw = (BitWriter *) calloc(sizeof(BitWriter), 1);
    if (bw == NULL) {
        return NULL;
    }
    bw->underlying_stream = fopen(filename, "wb");
    if (bw->underlying_stream == NULL) {
        free(bw);
        return NULL;
    }
    bw->byte = 0;
    bw->bit_position = 0;
    return bw;
}

void bit_write_close(BitWriter **pbuf) {
    if (*pbuf != NULL) {
        if ((*pbuf)->bit_position > 0) {
            fputc((*pbuf)->byte, (*pbuf)->underlying_stream);
        }
        fclose((*pbuf)->underlying_stream);
        free(*pbuf);
        *pbuf = NULL;
    }
}

void bit_write_bit(BitWriter *buf, uint8_t bit) {
    if (buf->bit_position > 7) {
        if (fputc(buf->byte, buf->underlying_stream) == EOF) {
            perror("fputc");
            exit(EXIT_FAILURE);
        }
        buf->byte = 0;
        buf->bit_position = 0;
    }
    buf->byte |= (bit << buf->bit_position);
    buf->bit_position += 1;
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (int i = 0; i < 16; i++) {
        bit_write_bit(buf, (x >> i) & 1);
    }
}

void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (int i = 0; i < 32; i++) {
        bit_write_bit(buf, (x >> i) & 1);
    }
}

void bit_write_uint8(BitWriter *buf, uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        bit_write_bit(buf, (byte >> i) & 1);
    }
}
