#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_usage(void) {
    printf("Usage: dehuff -i infile -o outfile\n");
    printf("       dehuff -v -i infile -o outfile\n");
    printf("       dehuff -h\n");
}

#define MAX_SIZE 64

Node *stack[MAX_SIZE];
int top = -1;

void stack_push(Node *element) {
    if (top < MAX_SIZE - 1) {
        top++;
        stack[top] = element;
    } else {
        fprintf(stderr, "Stack Overflow\n");
        exit(1);
    }
}

Node *stack_pop(void) {
    if (top >= 0) {
        Node *element = stack[top];
        top--;
        return element;
    } else {
        fprintf(stderr, "Stack Underflow\n");
        return NULL; // Indicate that the stack is empty
    }
}

void stack_free(void) {
    while (top >= 0) {
        free(stack[top]);
        top--;
    }
}

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    uint32_t filesize = bit_read_uint32(inbuf);
    uint16_t num_leaves = bit_read_uint16(inbuf);
    assert(type1 == 'H');
    assert(type2 == 'C');
    int num_nodes = 2 * num_leaves - 1;
    Node *node;

    // Read the tree
    for (int i = 0; i < num_nodes; i++) {
        int bit = bit_read_bit(inbuf);
        if (bit == 1) {
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            node = node_create(0, 0);
            node->right = stack_pop();
            node->left = stack_pop();
        }
        stack_push(node);
    }
    // get the root of the tree
    Node *code_tree = stack_pop();

    // Read the compressed data
    for (uint32_t i = 0; i < filesize; i++) {
        node = code_tree;
        while (true) {
            int bit = bit_read_bit(inbuf);
            if (bit == 0) {
                node = node->left;
            } else {
                node = node->right;
            }
            if (node->left == NULL) {
                break;
            }
        }
        fputc(node->symbol, fout);
    }
    node_free(&code_tree);
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

    BitReader *inbuf = bit_read_open(input_filename);

    // open output file
    FILE *fout = fopen(output_filename, "w");
    if (fout == NULL) {
        fprintf(stderr, "huff:  unable to open %s\n", output_filename);
        return EXIT_FAILURE;
    }

    dehuff_decompress_file(fout, inbuf);

    // close all
    bit_read_close(&inbuf);
    fclose(fout);
    stack_free();

    return EXIT_SUCCESS;
}
