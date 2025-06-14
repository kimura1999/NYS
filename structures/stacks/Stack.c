#include "Stack.h"

typedef struct Stack {
    LinkedList* list;
    int size;
} Stack;

bool STK_createStack(Stack **stack, DataType dataType, int (*isEqual)(GENERIC, GENERIC), void (*freeADT)(GENERIC)) {
    *stack = (Stack *)malloc(sizeof(Stack));
    if (!(*stack)) {
        return FALSE;
    }
    (*stack)->size = 0;
    if (!LK_createLinkedList(&(*stack)->list, dataType, isEqual, freeADT)) return FALSE;

    return TRUE;
}

void STK_freeStack(Stack *stack) {
    LK_freeLinkedList(stack->list);
    free(stack);
}

bool STK_isEmpty(Stack *stack) {
    return stack->size == 0;
}

int STK_getSize(Stack *stack) {
    return stack->size;
}

bool STK_push(Stack *stack, void* data) {
    if (LK_addData(stack->list, data)) {
        stack->size++;
        return TRUE;
    }
    return FALSE;
}

GENERIC STK_pop(Stack *stack) {
    if (STK_isEmpty(stack)) return NULL;

    GENERIC data = LK_getData(stack->list, 0);
    if (!LK_removeDataINDEX(stack->list, 0)) return NULL;
    stack->size--;
    return data;
}

GENERIC STK_peek(Stack *stack) {
    return LK_getData(stack->list, 0);
}
