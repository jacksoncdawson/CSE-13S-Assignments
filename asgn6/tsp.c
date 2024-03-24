#include "tsp.h"

#include "graph.h"
#include "path.h"
#include "stack.h"

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// gets a graph from a file stream
Graph *get_graph_from_stream(FILE *stream, bool isDirected) {
    uint32_t numVertices, numEdges;

    fscanf(stream, "%u\n", &numVertices);
    Graph *g = graph_create(numVertices, isDirected);

    for (uint32_t i = 0; i < numVertices; i++) {
        char name[100];
        if (fgets(name, sizeof(name), stream) != NULL) {
            size_t len = strlen(name);
            if (len > 0 && name[len - 1] == '\n') {
                name[len - 1] = '\0';
            }
            graph_add_vertex(g, name, i);
        }
    }

    fscanf(stream, "%u\n", &numEdges);

    for (uint32_t i = 0; i < numEdges; i++) {
        uint32_t start, end, weight;
        fscanf(stream, "%u %u %u\n", &start, &end, &weight);
        graph_add_edge(g, start, end, weight);
    }
    return g;
}

// unvisit all vertices in a graph
void unvisit_all_vertices(Graph *g) {
    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        graph_unvisit_vertex(g, i);
    }
}

// recursive function to find the shortest path
void tsp_dfs_visit(Graph *g, uint32_t currentVertex, uint32_t startVertex, Path *currentPath,
    Path *bestPath, uint32_t *minPathWeight) {
    graph_visit_vertex(g, currentVertex);
    path_add(currentPath, currentVertex, g);

    // If the path is complete, check if it is the best path
    if (path_vertices(currentPath) == graph_vertices(g)) {
        // Attempt to return to start vertex to complete the cycle
        uint32_t returnWeight = graph_get_weight(g, currentVertex, startVertex);
        if (returnWeight > 0 && path_distance(currentPath) + returnWeight < *minPathWeight) {
            *minPathWeight = path_distance(currentPath) + returnWeight;
            path_copy(bestPath, currentPath);
            path_add(bestPath, startVertex, g);
        }
    } else {
        for (uint32_t nextVertex = 0; nextVertex < graph_vertices(g); nextVertex++) {
            if (!graph_visited(g, nextVertex)
                && graph_get_weight(g, currentVertex, nextVertex) > 0) {
                tsp_dfs_visit(g, nextVertex, startVertex, currentPath, bestPath, minPathWeight);
            }
        }
    }

    // Backtrack
    graph_unvisit_vertex(g, currentVertex);
    path_remove(currentPath, g);
}

// Returns the best path found
Path *tsp_dfs(Graph *g, uint32_t start) {
    Path *bestPath = path_create(graph_vertices(g) + 1);
    Path *currentPath = path_create(graph_vertices(g) + 1);
    uint32_t minPathWeight = UINT32_MAX;

    unvisit_all_vertices(g);

    // get the best path
    tsp_dfs_visit(g, start, start, currentPath, bestPath, &minPathWeight);

    // if there is no valid path
    if (path_distance(bestPath) == 0) {
        fprintf(stdout, "No path found! Alissa is lost!\n");
        return NULL;
    }

    path_free(&currentPath);
    return bestPath;
}

// returns true if there is a vertex with no adjacent vertices
int hasIsolation(Graph *g) {
    // for every vertex
    for (uint32_t i = 0; i < graph_vertices(g); i++) {
        bool has_adjacent = false;

        // Check for any adjacent vertex
        for (uint32_t j = 0; j < graph_vertices(g); j++) {
            if (i != j && graph_get_weight(g, i, j) > 0) {
                has_adjacent = true;
                break;
            }
        }

        // If after checking all vertices, no adjacent vertex is found
        if (!has_adjacent) {
            fprintf(stdout, "No path found! Alissa is lost!\n");
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    bool isDirected = false;
    char *inputFileName = NULL;
    char *outputFileName = NULL;
    int opt;
    while ((opt = getopt(argc, argv, "i:o:dh")) != -1) {
        switch (opt) {
        case 'h': fprintf(stdout, "%s", USAGE); return 0;
        case 'i': inputFileName = optarg; break;
        case 'o': outputFileName = optarg; break;
        case 'd': isDirected = true; break;
        default: fprintf(stderr, "%s", BAD_OPTION); return 1;
        }
    }

    FILE *inputStream = inputFileName ? fopen(inputFileName, "r") : stdin;

    Graph *g = get_graph_from_stream(inputStream, isDirected);

    if (inputFileName) {
        fclose(inputStream);
    }

    // verify that the graph is contiguous
    if (hasIsolation(g)) {
        graph_free(&g);
        return 0;
    }

    // find the shortest path
    Path *shortestPath = tsp_dfs(g, 0);

    // if no valid path is returned, free and exit
    if (shortestPath == NULL) {
        graph_free(&g);
        return 0;
    }

    // print the path
    FILE *outputStream = outputFileName ? fopen(outputFileName, "w") : stdout;
    path_print(shortestPath, outputStream, g);

    if (outputFileName) {
        fclose(outputStream);
    }

    path_free(&shortestPath);
    graph_free(&g);

    return 0;
}
