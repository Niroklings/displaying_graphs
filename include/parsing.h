#ifndef PARSING_H
#define PARSING_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { digit, func, operator, left_scobka, right_scobka } TokenType;

struct Token {
    TokenType type;
    char value[40];
};

void removeSpaces(char* str);
int is_digit(char str);
int is_letter(char str);
int is_operator(char str);
int reading(char* str, struct Token* tokens);
int prov_digit(const char* str);
int is_func(const char* str);

#endif
