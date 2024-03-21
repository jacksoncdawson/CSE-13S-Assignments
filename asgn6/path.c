#include "path.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

Path *path_create(uint32_t capacity) {
    Path *p = calloc(1, sizeof(Path));
    p->total_weight = 0;
    p->vertices = stack_create(capacity);
    return p;
}

void path_free(Path **pp) {
    Path *p = *pp;
    stack_free(&p->vertices);
    free(p);
    *pp = NULL;
}

uint32_t path_vertices(const Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (stack_empty(p->vertices)) {
        stack_push(p->vertices, val);
        return;
    } else {
        uint32_t prev;
        if (stack_peek(p->vertices, &prev)) {
            stack_push(p->vertices, val);
            p->total_weight += graph_get_weight(g, prev, val);
        }
    }
}

uint32_t path_remove(Path *p, const Graph *g) {
    uint32_t val;
    if (!stack_pop(p->vertices, &val)) {
        return (uint32_t) -1;
    }

    if (stack_empty(p->vertices)) {
        return val;
    } else {
        uint32_t prev;
        if (stack_peek(p->vertices, &prev)) {
            p->total_weight -= graph_get_weight(g, prev, val);
        }
    }
    return val;
}

void path_copy(Path *dst, const Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->total_weight = src->total_weight;
    return;
}

void path_print(const Path *p, FILE *f, const Graph *g) {
    fprintf(f, "Alissa starts at:\n");

    stack_print(p->vertices, f, graph_get_names(g));

    fprintf(f, "Total Distance: %u\n", p->total_weight);
}
