#ifndef STACK_H
#define STACK_H

#include "../lists/LinkedList.h"

typedef struct Stack Stack;

bool STK_createStack(Stack **stack, DataType dataType, int (*isEqual)(GENERIC, GENERIC), void (*freeADT)(GENERIC));

void STK_freeStack(Stack *stack);

bool STK_isEmpty(Stack *stack);

int STK_getSize(Stack *stack);

bool STK_push(Stack *stack, void* data);

GENERIC STK_pop(Stack *stack);

GENERIC STK_peek(Stack *stack);

#endif //STACK_H
