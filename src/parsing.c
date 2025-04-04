#include "parsing.h"

#include "data_structures.h"
#include "polish_notation.h"

void removeSpaces(char* str) {
    int len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int is_digit(char str) {
    if ((str >= '0' && str <= '9') || str == '.' || str == 'x') {
        return 1;
    }
    else {
        return 0;
    }
    }
int is_letter(char str) { return (((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z')) && str != 'x'); }
int is_operator(char str) { return (str == '+' || str == '-' || str == '/' || str == '*'); }

int reading(char* str, struct Token* tokens) {
    int count = 0;
    removeSpaces(str);

    int i = 0;
    while (str[i] != '\0') {
        struct Token token;

        if (is_digit(str[i])) {
            int j = 0;
            while (str[i] != '\0' && is_digit(str[i]) && (j < (int)sizeof(token.value) - 1)) {
                token.value[j++] = str[i++];
            }
            token.value[j] = '\0';
            token.type = digit;
          //  printf("digit\n");
            tokens[count++] = token;
        }
        else if (str[i] != '\0' && is_letter(str[i])) {
            int j = 0;
            while (str[i] != '\0' && (j < (int)sizeof(token.value) - 1) && is_letter(str[i])) {
                token.value[j++] = str[i++];
            }
            token.value[j] = '\0';
            token.type = func;
          //  printf("func\n");
            tokens[count++] = token;
        }
        else if (str[i] != '\0' && is_operator(str[i])) {
            token.value[0] = str[i++];
            token.value[1] = '\0';
            token.type = operator;
          //  printf("oper\n");
            tokens[count++] = token;
        }
        else if (str[i] == '(') {
            token.value[0] = str[i++];
            token.value[1] = '\0';
            token.type = left_scobka;
          //  printf("lscob\n");
            tokens[count++] = token;
        }
        else if (str[i] == ')') {
            token.value[0] = str[i++];
            token.value[1] = '\0';
            token.type = right_scobka;
           // printf("rscob\n");
            tokens[count++] = token;
        }
        else {
            return -1;
        }
    }
    return count;
}

int prov_digit(const char* str) {
    int i = 0;
    int count_of_t = 0;
    if(str[0] == '0' && str[1] == '0'){
        return 0;
    }
    while (str[i] != '\0') {
        if (str[i] == '.') {
            count_of_t++;
            if (i == 0 || i == (int)strlen(str) - 1) {
                return 0;
            }
        }
        if (count_of_t > 1) {
            return 0;
        }
        i++;
    }
    return 1;
}

int is_func(const char* str) {
    if (strcmp(str, "sin") == 0 || strcmp(str, "cos") == 0 || strcmp(str, "tan") == 0 ||
        strcmp(str, "ctg") == 0 || strcmp(str, "sqrt") == 0 || strcmp(str, "ln") == 0) {
        return 1;
    }
    return 0;
}
