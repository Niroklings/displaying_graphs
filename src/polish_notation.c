#include "polish_notation.h"

#include <math.h>
int is_op1(const char* str) {
    if (strcmp(str, "-") == 0 || strcmp(str, "+") == 0) {
        return 1;
    }
    return 0;
}

int is_op2(const char* str) {
    if (strcmp(str, "*") == 0 || strcmp(str, "/") == 0) {
        return 1;
    }
    return 0;
}

int precedece(const char* str) {
    if (is_op2(str)) return 2;
    if (is_op1(str)) return 1;
    return 0;
}

void typeDigit(Queue* queue, struct Token* token, int i) { enqueue(queue, token[i]); }

void typeFunc(Stack* stack, struct Token* token, int i) { stackPush(stack, &token[i]); }

void typeOper(Stack* stack, Queue* queue, struct Token* token, int i) {
    while (!stackIsEmpty(stack) && precedece(stackPeek(stack).value) >= precedece(token[i].value) &&
        strcmp(stackPeek(stack).value, "(") != 0) {
        enqueue(queue, stackPeek(stack));
        stackPop(stack);
    }
    stackPush(stack, &token[i]);
}

void typeLeft(Stack* stack, struct Token* token, int i) { stackPush(stack, &token[i]); }

void typeRight(Stack* stack, Queue* queue) {
    while (!stackIsEmpty(stack) && strcmp(stackPeek(stack).value, "(") != 0) {
        enqueue(queue, stackPeek(stack));
        stackPop(stack);
    }
    if (stackIsEmpty(stack)) {
        freeQueue(queue);
        freeStack(stack);
        return;
    }
    stackPop(stack);

    if (!stackIsEmpty(stack) && is_func(stackPeek(stack).value)) {
        enqueue(queue, stackPeek(stack));
        stackPop(stack);
    }
}

Queue* polish(int count, struct Token* token) {
    Queue* queue = createQueue(count);
    if (!queue) return NULL;
    Stack* stack = createStack(count);
    if (!stack) {
        freeQueue(queue);
        return NULL;
    }
    int i = 0;
    while (i < count) {
        if (token[i].type == digit) {
            typeDigit(queue, token, i);
        }
        else if (token[i].type == func) {
            typeFunc(stack, token, i);
        }
        else if ((token[i].type == operator) && precedece(token[i].value) > 0) {
            typeOper(stack, queue, token, i);
        }
        else if (token[i].type == left_scobka) {
            typeLeft(stack, token, i);
        }
        else if (token[i].type == right_scobka) {
            typeRight(stack, queue);
        }
        i++;
    }
    while (!stackIsEmpty(stack)) {
        struct Token top = stackPeek(stack);
        if (strcmp(top.value, "(") == 0 || strcmp(top.value, ")") == 0) {
            freeQueue(queue);
            freeStack(stack);
            return NULL;
        }
        enqueue(queue, stackPeek(stack));
        stackPop(stack);
    }
    freeStack(stack);
    return queue;
}

double calculation(Queue* queue, int count, double x) {
    struct dStack* stack = dcreateStack(count);
    struct Token* token = (struct Token*)malloc(sizeof(struct Token));
    
    while (!(queueIsEmpty(queue))) {
        //printQueue(queue);
        double a;
        *token = queuePeek(queue);

        dequeue(queue);

        if (is_digit(token->value[0])) {
            if (strcmp(token->value, "x") == 0) {
                dstackPush(stack, &x);
            }
            else {
                a = atof(token->value);
                dstackPush(stack, &a);
            }
        }
        else if (is_operator(token->value[0])) {

            if ((strcmp(token->value, "-") == 0) && queueIsEmpty(queue)) {
                if (dstackIsEmpty(stack)) {
                    printf("������ �������� ������\n");
                    printf("������ �������\n");
                    dfreeStack(stack);
                }
                double oper1 = 0;
                oper1 = dstackPeek(stack);
                dstackPop(stack);
                a = -oper1;
                dstackPush(stack, &a);
            }
            else {
                if (dstackSize(stack) < 2) {
                    printf("������ ��������� ������\n");
                    dfreeStack(stack);
                    free(token);
                    return NAN;
                }
                double oper1 = 0, oper2 = 0;
                oper2 = dstackPeek(stack);
                dstackPop(stack);
                oper1 = dstackPeek(stack);
                dstackPop(stack);
                if (strcmp(token->value, "+") == 0) {
                    a = oper1 + oper2;
                    dstackPush(stack, &a);
                }
                else if (strcmp(token->value, "-") == 0) {
                    a = oper1 - oper2;
                    dstackPush(stack, &a);
                }
                else if (strcmp(token->value, "*") == 0) {
                    a = oper1 * oper2;
                    dstackPush(stack, &a);
                }
                else if (strcmp(token->value, "/") == 0) {
                    if (oper2 == 0) {
                        printf("������� �� 0\n");
                        dfreeStack(stack);
                        free(token);
                        return NAN;
                    }
                    a = oper1 / oper2;
                    dstackPush(stack, &a);
                }
            }
        }
        else {

            if (is_func(token->value)) {
                if (dstackIsEmpty(stack)) {
                    dfreeStack(stack);
                    free(token);
                    return NAN;
                }
                double operand = 0;
                operand = dstackPeek(stack);
                dstackPop(stack);
                if (strcmp(token->value, "sin") == 0) {
                    a = sin(operand);

                    dstackPush(stack, &a);
                }
                else if (strcmp(token->value, "cos") == 0) {
                    a = cos(operand);
                    dstackPush(stack, &a);
                }
                else if (strcmp(token->value, "tan") == 0) {
                    a = tan(operand);
                    dstackPush(stack, &a);
                }
                else if (strcmp(token->value, "ctg") == 0) {
                    if (tan(operand) == 0) {
                        printf("ctg �� ����������\n");
                        dfreeStack(stack);
                        free(token);
                        return NAN;
                    }
                    a = 1.0 / tan(operand);
                    dstackPush(stack, &a);

                }
                else if (strcmp(token->value, "sqrt") == 0) {
                    if (operand < 0) {
                        printf("sqrt �� ����������\n");
                        dfreeStack(stack);
                        free(token);
                        return NAN;
                    }
                    a = sqrt(operand);
                    dstackPush(stack, &a);
                }
            }
            else {
                printf("������ �������\n");
                dfreeStack(stack);
                free(token);
                return NAN;
            }
        }
    }
   // dPrintStack(stack);
    if (dstackSize(stack) != 1) {
        printf("������. �������� �������� � �����.\n");
        free(token);
        dfreeStack(stack);
        return NAN;
    }
    double result = dstackPeek(stack);
    free(token);
    dstackPop(stack);
    dfreeStack(stack);
    return result;
}
