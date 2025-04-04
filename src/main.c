#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <float.h>
#include "data_structures.h"
#include "parsing.h"
#include "polish_notation.h"
#include "graphics.h"
#include "validation.h"
#include "constants.h"

int main() {
    char str[MAX_LEN];
   
    printf("Введите функцию (макс %d символов): ", MAX_LEN-1);
    scanf("%s", str);

    struct Token* token = (struct Token*)malloc(strlen(str) * sizeof(struct Token));

    int count = reading(str, token);
    if (count == -1) {
        printf("Ошибка чтения строки\n");
        free(token);
        return 0;
    }

    if (!validate_tokens(token, count)) {
        free(token);
        return 1;
    }

    Queue* queue = polish(count, token);
    if (queue == NULL) {
        printf("Ошибка выделения памяти");
        free(token);
        return 1;
    }

    char graph[GRAPH_HEIGHT][GRAPH_WIDTH];
    char y_labels[GRAPH_HEIGHT][Y_LABEL_WIDTH];
    char x_labels[GRAPH_WIDTH][5];

    double x_min = -2 * PI;
    double x_max = 2 * PI;
    GraphLimits limits = determine_limits(queue, count, x_min, x_max);

    for (int y = 0; y < GRAPH_HEIGHT; y++) {
        double y_value = limits.max_y - (limits.max_y - limits.min_y) * y / (GRAPH_HEIGHT - 1);
        snprintf(y_labels[y], Y_LABEL_WIDTH, "%6.2f", y_value);
    }

    for (int x = 0; x < GRAPH_WIDTH; x++) {
        double x_value = limits.min_x + (limits.max_x - limits.min_x) * x / (GRAPH_WIDTH - 1);
        snprintf(x_labels[x], 5, "%.1f", x_value);
    }

    draw_graph(graph, limits, queue, count);

    for (int y = 0; y < GRAPH_HEIGHT; y++) {
        printf("%s ", y_labels[y]);
        for (int x = 0; x < GRAPH_WIDTH; x++) {
            printf("%c", graph[y][x]);
        }
        printf("\n");
    }

    printf("%*s", Y_LABEL_WIDTH + 1, "");
    for (int x = 0; x < GRAPH_WIDTH; x += 10) {
        printf("%-10s", x_labels[x]);
    }
    printf("\n");
    
    freeQueue(queue);
    free(token);
    return 0;
}