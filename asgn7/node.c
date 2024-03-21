//node.c

#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void node_print_node(Node *tree, char ch, int indentation);

Node *node_create(uint8_t symbol, uint32_t weight) {
    Node *node = (Node *) calloc(sizeof(Node), 1);
    if (node == NULL) {
        return NULL;
    }
    node->symbol = symbol;
    node->weight = weight;
    return node;
}

void node_free(Node **node) {
    if (*node != NULL) {
        node_free(&(*node)->left);
        node_free(&(*node)->right);
        free(*node);
        *node = NULL;
    }
}

void node_print_node(Node *tree, char ch, int indentation) {
    if (tree == NULL) {
        return;
    }
    node_print_node(tree->right, '/', indentation + 3);
    printf("%*cweight = %d", indentation + 1, ch, tree->weight);
    if (tree->left == NULL && tree->right == NULL) {
        if (' ' <= tree->symbol && tree->symbol <= '~') {
            printf(", symbol = '%c'", tree->symbol);
        } else {
            printf(", symbol = 0x%02x", tree->symbol);
        }
    }
    printf("\n");
    node_print_node(tree->left, '\\', indentation + 3);
}

void node_print_tree(Node *tree) {
    node_print_node(tree, '<', 2);
}
