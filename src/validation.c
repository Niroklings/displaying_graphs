#include "validation.h"
#include "parsing.h"

int validate_tokens(struct Token* tokens, int count) {
    int count_left_scobka = 0;
    int count_right_scobka = 0;
    
    for (int i = 0; i < count; i++) {
        if (tokens[i].type == digit) {
            if (prov_digit(tokens[i].value) == 0) {
                printf("Ошибка числа\n");
                return 0;
            }
        }
        else if (tokens[i].type == func) {
            if (is_func(tokens[i].value) == 0) {
                printf("Ошибка функции\n");
                return 0;
            }
        } 
        else if(tokens[i].type == left_scobka) {
            count_left_scobka++;
        } 
        else if(tokens[i].type == right_scobka) {
            count_right_scobka++;
        }
    }
    
    if(count_left_scobka != count_right_scobka) {
        printf("Ошибка скобок\n");
        return 0;
    }
    
    return 1;
}