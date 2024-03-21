// huff.c

#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void bit_flush(BitWriter *buf);

typedef struct Code {
    uint64_t code;
    uint8_t code_length;
} Code;

void print_usage(void) {
    printf("Usage: huff -i infile -o outfile\n");
    printf("       huff -v -i infile -o outfile\n");
    printf("       huff -h\n");
}

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    uint32_t filesize = 0;

    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    int c;
    while ((c = fgetc(fin)) != EOF) {
        histogram[c]++;
        filesize++;
    }
    histogram[0x00]++;
    histogram[0xff]++;
    return filesize;
}

Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
    PriorityQueue *pq = pq_create();
    for (int i = 0; i < 256; i++) {
        if (histogram[i] > 0) {
            Node *node = node_create((uint8_t) i, (uint32_t) histogram[i]);
            enqueue(pq, node);
            (*num_leaves)++;
        }
    }

    while (!pq_is_empty(pq) && !pq_size_is_1(pq)) {
        Node *left = dequeue(pq);
        Node *right = dequeue(pq);
        Node *node = node_create(0, left->weight + right->weight);
        node->left = left;
        node->right = right;
        enqueue(pq, node);
    }
    Node *tree = dequeue(pq);
    pq_free(&pq);
    return tree;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    // if node is internal
    if (node->left != NULL) { // branch node
        fill_code_table(code_table, node->left, code, code_length + 1);
        uint64_t code_right = code | ((uint64_t) 1 << code_length);
        fill_code_table(code_table, node->right, code_right, code_length + 1);
    } else {
        // Leaf node, store the code and its length
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) { // leaf node
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    } else { // internal node
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    }
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);
    huff_write_tree(outbuf, code_tree);

    while (true) {
        int c = fgetc(fin);
        if (c == EOF) {
            break;
        }
        uint64_t code = code_table[c].code;
        uint8_t code_length = code_table[c].code_length;
        for (int i = 0; i < code_length; i++) {
            bit_write_bit(outbuf, code & 1);
            code >>= 1;
        }
    }
}

int main(int argc, char *argv[]) {
    int opt;
    char *input_filename = NULL;
    char *output_filename = NULL;

    while ((opt = getopt(argc, argv, "i:o:h")) != -1) {
        switch (opt) {
        case 'i': input_filename = optarg; break;
        case 'o': output_filename = optarg; break;
        case 'h': print_usage(); return EXIT_SUCCESS;
        default: print_usage(); return EXIT_FAILURE;
        }
    }

    // validate command line arguments
    if (input_filename == NULL || output_filename == NULL) {
        if (input_filename == NULL) {
            fprintf(stderr, "huff:  -i option is required\n");
        }
        if (output_filename == NULL) {
            fprintf(stderr, "huff:  -o option is required\n");
        }
        print_usage();
        return EXIT_FAILURE;
    }

    // open input file
    FILE *fin = fopen(input_filename, "r");
    if (fin == NULL) {
        fprintf(stderr, "huff:  unable to open %s\n", input_filename);
        return EXIT_FAILURE;
    }

    // fill histogram
    uint32_t histogram[256];
    uint32_t filesize = fill_histogram(fin, histogram);
    // rewind file
    fseek(fin, 0, SEEK_SET);

    // create huffman tree
    uint16_t num_leaves = 0;
    Node *code_tree = create_tree(histogram, &num_leaves);

    // create code table
    Code code_table[256];
    fill_code_table(code_table, code_tree, 0, 0);

    // setup bitwriter
    BitWriter *bw = bit_write_open(output_filename);
    if (bw == NULL) {
        fprintf(stderr, "huff: unable to create BitWriter for %s\n", output_filename);
        fclose(fin);
        return EXIT_FAILURE;
    }

    // compress file
    huff_compress_file(bw, fin, filesize, num_leaves, code_tree, code_table);

    // close bitwriter
    bit_write_close(&bw);

    // close input file
    fclose(fin);

    // free
    node_free(&code_tree);

    return EXIT_SUCCESS;
}
