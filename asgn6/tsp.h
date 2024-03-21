
#include <stdbool.h>

#ifndef __TSP_H__
#define __TSP_H__

#define BAD_OPTION "tsp:  unknown or poorly formatted option -n\n"

#define USAGE                                                                                      \
    "Usage: tsp [options]\n\n"                                                                     \
    "-i infile    Specify the input file path containing the cities and edges\n"                   \
    "             of a graph. If not specified, the default input should be\n"                     \
    "             set as stdin.\n\n"                                                               \
    "-o outfile   Specify the output file path to print to. If not specified,\n"                   \
    "             the default output should be set as stdout.\n\n"                                 \
    "-d           Specifies the graph to be directed.\n\n"                                         \
    "-h           Prints out a help message describing the purpose of the\n"                       \
    "             graph and the command-line options it accepts, exiting the\n"                    \
    "             program afterwards.\n"

#endif
