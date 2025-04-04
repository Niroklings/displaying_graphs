#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "data_structures.h"
#include "constants.h"

typedef struct {
    double min_x, max_x;
    double min_y, max_y;
} GraphLimits;

GraphLimits determine_limits(Queue* queue, int count, double x_min, double x_max);
void draw_graph(char graph[GRAPH_HEIGHT][GRAPH_WIDTH], GraphLimits limits, Queue* queue, int count);

#endif