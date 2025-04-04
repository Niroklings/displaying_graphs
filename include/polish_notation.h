#ifndef POLISH_H
#define POLISH_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_structures.h"
#include "parsing.h"
int is_op1(const char* str);
int is_op2(const char* str);
int precedece(const char* str);
void typeDigit(Queue* queue, struct Token* token, int i);
void typeFunc(Stack* stack, struct Token* token, int i);
void typeOper(Stack* stack, Queue* queue, struct Token* token, int i);
void typeLeft(Stack* stack, struct Token* token, int i);
void typeRight(Stack* stack, Queue* queue);
Queue* polish(int count, struct Token* token);
double calculation(Queue* queue, int count, double x);
#endif
