// pq.c

#include "pq.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListElement ListElement;
struct ListElement {
    Node *tree;
    ListElement *next;
};
struct PriorityQueue {
    ListElement *list;
};

PriorityQueue *pq_create(void) {
    PriorityQueue *pq = (PriorityQueue *) calloc(sizeof(PriorityQueue), 1);
    if (pq == NULL) {
        return NULL;
    }
    pq->list = NULL;
    return pq;
}

void pq_free(PriorityQueue **q) {
    if (*q == NULL) {
        return;
    }
    ListElement *current = (*q)->list;
    while (current != NULL) {
        ListElement *temp = current;
        current = current->next;
        free(temp);
    }
    free(*q);
    *q = NULL;
}

bool pq_is_empty(PriorityQueue *q) {
    if (q->list == NULL) {
        return true;
    }
    return false;
}

bool pq_size_is_1(PriorityQueue *q) {
    if (q->list == NULL) {
        return false;
    }
    if (q->list->next == NULL) {
        return true;
    }
    return false;
}

bool pq_less_than(ListElement *e1, ListElement *e2) {
    if (e1->tree->weight < e2->tree->weight) {
        return true;
    } else if (e1->tree->weight == e2->tree->weight) {
        if (e1->tree->symbol < e2->tree->symbol) {
            return true;
        }
    }
    return false;
}

void enqueue(PriorityQueue *q, Node *tree) {
    ListElement *new = (ListElement *) calloc(sizeof(ListElement), 1);
    if (new == NULL) {
        return;
    }
    new->tree = tree;

    // The queue currently is empty.
    if (q->list == NULL) {
        q->list = new;
        return;
    }

    // The new element will become the new first element of the queue.
    if (pq_less_than(new, q->list)) {
        new->next = q->list;
        q->list = new;
        return;
    }

    // The new element will be placed after an existing element.
    ListElement *current = q->list;
    // while we are not at the last node, and the new element is less than the next element
    while (current->next != NULL && pq_less_than(current->next, new)) {
        current = current->next;
    }
    new->next = current->next;
    current->next = new;
}

Node *dequeue(PriorityQueue *q) {
    if (q->list == NULL) {
        fprintf(stderr, "Fatal error: dequeue called on an empty queue\n");
        exit(1);
    }

    ListElement *temp = q->list;
    q->list = q->list->next;
    Node *tree = temp->tree;
    free(temp);
    return tree;
}

void pq_print(PriorityQueue *q) {
    assert(q != NULL);
    ListElement *e = q->list;
    int position = 1;

    while (e != NULL) {
        if (position++ == 1) {
            printf("=============================================\n");
        } else {
            printf("---------------------------------------------\n");
        }
        node_print_tree(e->tree);
        e = e->next;
    }
    printf("=============================================\n");
}
