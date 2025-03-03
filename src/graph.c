#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <crtdbg.h> //ctrl+shift+B F5


#define HEIGHT 25
#define WIDTH 80
#define coordinate_center_y 12
#define PI 3.14159265358979323846

#include "data_structures.h"
#include "parsing.h"
#include "polish_notation.h"


int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //�������� �� ������
    setlocale(LC_ALL, "");
    char *str = NULL;
    int len_str = 0;
    int read = getline(&str, &len_str, stdin);
    if(read != -1){
        if(str[read - 1] == '\n'){
            str[read - 1] = '\0';
        }
    } else{
        printf("0ошибка строки\n");
        free(str);
        return 1;
    }


    struct Token* token = (struct Token*)malloc(strlen(str) * sizeof(struct Token));

    int count = reading(str, token);
    if (count == -1) {
        printf("n/a\n");
        free(str);
        return 0;
    }
    int count_left_scobka = 0;
    int count_right_scobka = 0;
    for (int i = 0; i < count; i++) {
        if (token[i].type == digit) {
            if (prov_digit(token[i].value) == 0) {
                printf("1ошибка числа\n");
                free(str);
                free(token);
                return 1;
            }
        }
        else if (token[i].type == func) {
            if (is_func(token[i].value) == 0) {
                printf("2ошибка функции\n");
                free(str);
                free(token);
                return 1;
            }
        } else if(token[i].type == left_scobka){
            count_left_scobka++;
        } else if(token[i].type == right_scobka){
            count_right_scobka++;
        }
    }
    if(count_left_scobka != count_right_scobka){
        printf("3ошибка скобок\n");
        free(str);
        free(token);
        return 1;
    }

    Queue* queue = polish(count, token);
    if (queue == NULL) {
        printf("n/a");
        free(str);
        return 1;
    }
    char screen[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            screen[i][j] = '.';
        }
    }

    double x = 0;
   // printQueue(queue);
    for (int x_pixel = 0; x_pixel < WIDTH; x_pixel++) {
        x = (4 * PI * x_pixel) / (WIDTH - 1);
       // printf("%d\n", x_pixel);
        Queue* temp_queue = copyQueue(queue, count);
        double y = calculation(temp_queue, count, x);
       // printf("%lf :    %lf\n", x, y);
        if (isnan(y)) {
            freeQueue(temp_queue);
            continue;
        }
        int y_pixel = (int)round((coordinate_center_y - (y  / 2) * (HEIGHT - 1)));
       // printf("����������:  %d %d\n", x_pixel, y_pixel);
        
        if (y_pixel >= 0 && y_pixel < HEIGHT) {
            screen[y_pixel][x_pixel] = '*';
        }
        freeQueue(temp_queue);
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
    free(str);
    freeQueue(queue);
    free(token);
    return 0;
}
