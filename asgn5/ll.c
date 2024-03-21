#include "ll.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

LL *list_create() {
    LL *l = (LL *) calloc(1, sizeof(LL));
    if (l == NULL) {
        return NULL;
    }
    l->head = NULL;
    return l;
}

bool list_add(LL *l, item *i) {
    Node *n = (Node *) calloc(1, sizeof(Node));
    if (n == NULL) {
        return false;
    }
    n->data = *i;
    n->next = NULL;
    // if the list is empty...
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
    }
    // if the list is not empty...
    else {
        // add the new node to the end of the list
        l->tail->next = n;
        // set the tail of the list to the new node
        l->tail = n;
    }
    return true;
}

item *list_find(LL *l, bool (*cmp)(item *, item *), item *i) {
    Node *n = l->head;
    while (n != NULL) {
        if (cmp(&n->data, i)) {
            return &n->data;
        }
        n = n->next;
    }
    return NULL;
}

void list_destroy(LL **l) {
    Node *n = (*l)->head;
    while (n != NULL) {
        Node *next = n->next;
        free(n);
        n = next;
    }
    free(*l);
    *l = NULL;
    return;
}

void list_remove(LL *l, bool (*cmp)(item *, item *), item *i) {
    Node *n = l->head;
    Node *prev = NULL;
    while (n != NULL) {
        if (cmp(&n->data, i)) {
            // if the node to remove is the head...
            if (prev == NULL) {
                l->head = n->next;
                if (l->head == NULL) {
                    l->tail = NULL;
                }
            }
            // if the node to remove is not the head...
            else {
                prev->next = n->next;
                if (n->next == NULL) {
                    l->tail = prev;
                }
            }
            free(n);
            return;
        }
        // move to the next node
        prev = n;
        n = n->next;
    }
    return;
}
