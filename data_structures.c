#include "data_structures.h"
//#define _CRT_SECURE_NO_WARNINGS

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->top = NULL;
    stack->size = 0;
    stack->capacity = capacity;
    return stack;
}

int stackIsEmpty(Stack* stack) { return (stack->top == NULL); }

int stackIsFull(Stack* stack) { return (stack->capacity != 0 && stack->size == stack->capacity); }

void stackPop(Stack* stack) {
    if (stackIsEmpty(stack)) return;
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
}
/*
void stackPush(Stack* stack, struct Token* data) {
    if (stackIsFull(stack)) return;

    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) return;
    strcpy(newNode->token.value, data->value);
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}*/
// Функция для добавления токена в стек
void stackPush(Stack* stack, struct Token* data) {
    if (stackIsFull(stack)) return;

    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) return;

    // Копируем тип и значение токена
    newNode->token.type = data->type; // Копируем тип токена
    strncpy(newNode->token.value, data->value, sizeof(newNode->token.value) - 1);
    newNode->token.value[sizeof(newNode->token.value) - 1] = '\0'; // Завершаем строку
    newNode->next = stack->top; // Узел указывает на предыдущий верхний узел
    stack->top = newNode; // Обновляем верхний узел стека
    stack->size++; // Увеличиваем размер стека
}
void freeStack(Stack* stack) {
    StackNode* current = stack->top;
    StackNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(stack);
}

struct Token stackPeek(Stack* stack) { return stack->top->token; }
////////////////////////////DSTACK
double dstackPeek(dStack* stack) { return stack->top->data; }

dStack* dcreateStack(int capacity) {
    dStack* stack = (dStack*)malloc(sizeof(dStack));
    if (!stack) return NULL;
    stack->top = NULL;
    stack->size = 0;
    stack->capacity = capacity;
    return stack;
}

void dPrintStack(dStack* stack) {
    if (stack == NULL || stack->top == NULL) {
        printf("Стек пуст.\n");
        return;
    }

    dStackNode* current = stack->top;
    printf("Содержимое стека (сверху вниз):\n");
    while (current != NULL) {
        printf("%lf\n", current->data); // Выводим значение double
        current = current->next; // Переход к следующему узлу
    }
}

void dfreeStack(dStack* stack) {
    dStackNode* current = stack->top;
    dStackNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(stack);
}
int dstackSize(dStack* stack) { return stack->size; }
int dstackIsEmpty(dStack* stack) { return (stack->top == NULL); }

void dstackPush(dStack* stack, const double* data) {
    dStackNode* newNode = (dStackNode*)malloc(sizeof(dStackNode));
    if (!newNode) return;
    newNode->data = *data;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

void dstackPop(dStack* stack) {
    if (dstackIsEmpty(stack)) return;
    dStackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
}

/////////////////////////////////QUEUE
Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

int queueIsEmpty(Queue* queue) { return (queue->front == NULL); }

int queueIsFull(Queue* queue) { return (queue->size == queue->capacity); }

Queue* copyQueue(Queue* original, int count) {
    if (original == NULL) return NULL;

    Queue* newQueue = createQueue(count);
    QueueNode* current = original->front;

    while (current != NULL) {
        enqueue(newQueue, current->token);
        current = current->next;
    }

    return newQueue;
}
void enqueue(Queue * queue, struct Token data) {
    if (queue->capacity != 0 && queueIsFull(queue)) return;

    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) return;

    // Копируем все данные токена
    newNode->token.type = data.type; // Копируем тип токена
    strncpy(newNode->token.value, data.value, sizeof(newNode->token.value) - 1);
    newNode->token.value[sizeof(newNode->token.value) - 1] = '\0'; // Безопасное завершение строки
    newNode->next = NULL;

    if (queueIsEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    queue->size++;
}

void dequeue(Queue* queue) {
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) queue->rear = NULL;

    free(temp);
    queue->size--;
}

struct Token queuePeek(Queue* queue) { return queue->front->token; }

void printQueue(Queue* queue) {
    if (queue == NULL || queue->front == NULL) {
        printf("Очередь пуста.\n");
        return;
    }

    QueueNode* current = queue->front;
    printf("Содержимое очереди:\n");
    while (current != NULL) {
        // Выводим тип токена и его значение
        printf("Тип токена: ");
        switch (current->token.type) {
        case digit:
            printf("digit");
            break;
        case func:
            printf("func");
            break;
        case operator:
            printf("operator");
            break;
        case left_scobka:
            printf("left_scobka");
            break;
        case right_scobka:
            printf("right_scobka");
            break;
        default:
            printf("неизвестный тип");
        }
        printf(", Значение: %s\n", current->token.value);
        current = current->next;
    }
}

void freeQueue(Queue* queue) {
    QueueNode* current = queue->front;
    QueueNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(queue);
}
