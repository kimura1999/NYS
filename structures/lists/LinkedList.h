#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

#include "../macros.h"

typedef struct LinkedList LinkedList;

int LK_getSize(LinkedList* linkedList);

bool LK_createLinkedList(LinkedList **linkedList, const DataType dataType,
    bool (*isEqual)(GENERIC, GENERIC), void (*freeADT)(GENERIC));

bool LK_isEmpty(LinkedList *linkedList);

GENERIC LK_getData(LinkedList *linkedList, unsigned int index);

bool LK_addData(LinkedList *linkedList, GENERIC data);

void LK_freeLinkedList(LinkedList *linkedList);

GENERIC* LK_toArray(LinkedList* linkedList);

bool LK_removeDataSEARCH(LinkedList *linkedList, GENERIC data);

bool LK_removeDataINDEX(LinkedList *linkedList, unsigned int index);

bool LK_containsData(LinkedList *linkedList, void* data, DataType dataType);

void LK_print(LinkedList *linkedList, void (*printADT)(GENERIC));

#endif //LINKEDLIST_H
