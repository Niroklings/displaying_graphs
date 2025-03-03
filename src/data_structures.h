#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsing.h"

#define STACK_EMPTY_ERROR ""
#define QUEUE_EMPTY_ERROR ""

typedef struct StackNode {
    struct Token token;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
    int size;
    int capacity;
} Stack;

typedef struct dStackNode {
    double data;
    struct dStackNode* next;
} dStackNode;

typedef struct dStack {
    dStackNode* top;
    int size;
    int capacity;
} dStack;

typedef struct QueueNode {
    struct Token token;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;
    int capacity;
} Queue;

Stack* createStack(int capacity);
int stackIsEmpty(Stack* stack);
int stackIsFull(Stack* stack);
void stackPush(Stack* stack, struct Token* data);
void stackPop(Stack* stack);
struct Token stackPeek(Stack* stack);
void freeStack(Stack* stack);

dStack* dcreateStack(int capacity);
int dstackIsEmpty(dStack* stack);
int dstackIsFull(dStack* stack);
void dstackPush(dStack* stack, const double* data);
void dstackPop(dStack* stack);
double dstackPeek(dStack* stack);
int dstackSize(dStack* stack);
void dPrintStack(dStack* stack);
void dfreeStack(dStack* stack);

Queue* createQueue(int capacity);
Queue* copyQueue(Queue* original, int count);
int queueIsEmpty(Queue* queue);
int queueIsFull(Queue* queue);
void enqueue(Queue* queue, struct Token data);
void dequeue(Queue* queue);
struct Token queuePeek(Queue* queue);
void printQueue(Queue* queue);

void freeQueue(Queue* queue);

#endif
