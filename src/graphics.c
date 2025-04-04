#include <math.h>
#include <float.h>
#include "graphics.h"
#include "data_structures.h"
#include "polish_notation.h"
#include "constants.h"

GraphLimits determine_limits(Queue* queue, int count, double x_min, double x_max) {
    GraphLimits limits = {x_min, x_max, DBL_MAX, -DBL_MAX};
    double step = (x_max - x_min) / SAMPLE_POINTS;
    
    for (int i = 0; i <= SAMPLE_POINTS; i++) {
        double x = x_min + i * step;
        Queue* temp_queue = copyQueue(queue, count);
        double y = calculation(temp_queue, count, x);
        freeQueue(temp_queue);
        
        if (!isnan(y) && !isinf(y)) {
            if (y < limits.min_y) limits.min_y = y;
            if (y > limits.max_y) limits.max_y = y;
        }
    }
    
    if (limits.min_y == DBL_MAX) {
        limits.min_y = -1.0;
        limits.max_y = 1.0;
    } else {
        double y_margin = (limits.max_y - limits.min_y) * 0.1;
        limits.min_y -= y_margin;
        limits.max_y += y_margin;
    }
    
    return limits;
}

void draw_graph(char graph[GRAPH_HEIGHT][GRAPH_WIDTH], GraphLimits limits, Queue* queue, int count) {
    for (int y = 0; y < GRAPH_HEIGHT; y++) {
        for (int x = 0; x < GRAPH_WIDTH; x++) {
            graph[y][x] = ' ';
        }
    }

    int zero_y = (int)round((limits.max_y - 0) / (limits.max_y - limits.min_y) * (GRAPH_HEIGHT - 1));
    int zero_x = (int)round((0 - limits.min_x) / (limits.max_x - limits.min_x) * (GRAPH_WIDTH - 1));
    
    if (zero_y >= 0 && zero_y < GRAPH_HEIGHT) {
        for (int x = 0; x < GRAPH_WIDTH; x++) {
            graph[zero_y][x] = '-';
        }
    }
    
    if (zero_x >= 0 && zero_x < GRAPH_WIDTH) {
        for (int y = 0; y < GRAPH_HEIGHT; y++) {
            graph[y][zero_x] = '|';
        }
    }
    
    if (zero_y >= 0 && zero_y < GRAPH_HEIGHT && zero_x >= 0 && zero_x < GRAPH_WIDTH) {
        graph[zero_y][zero_x] = '+';
    }

    for (int x_pixel = 0; x_pixel < GRAPH_WIDTH; x_pixel++) {
        double x = limits.min_x + (limits.max_x - limits.min_x) * x_pixel / (GRAPH_WIDTH - 1);
        
        Queue* temp_queue = copyQueue(queue, count);
        double y = calculation(temp_queue, count, x);
        freeQueue(temp_queue);
        
        if (isnan(y) || isinf(y)) continue;
        
        int y_pixel = (int)round((limits.max_y - y) / (limits.max_y - limits.min_y) * (GRAPH_HEIGHT - 1));
        
        if (y_pixel >= 0 && y_pixel < GRAPH_HEIGHT) {
            graph[y_pixel][x_pixel] = '*';
        }
    }
}