#include "LinkedList.h"

#include <stdio.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    int size;
    DataType dataType;

    bool (*isEqual)(GENERIC, GENERIC);
    void (*freeADT)(GENERIC);
} LinkedList;

int LK_getSize(LinkedList* linkedList) {
    return linkedList->size;
}

bool LK_createLinkedList(LinkedList **linkedList, const DataType dataType,
    bool (*isEqual)(GENERIC, GENERIC), void (*freeADT)(GENERIC)) {


    if (dataType < 0 || dataType > 8) return FALSE;

    *linkedList = malloc(sizeof(LinkedList));
    if (*linkedList == NULL) return FALSE;

    (*linkedList)->head = NULL;
    (*linkedList)->size = 0;
    (*linkedList)->dataType = dataType;


    if (dataType == TYPE_ADT) {
        if (isEqual == NULL || freeADT == NULL) {
            free(*linkedList);
            *linkedList = NULL;
            return FALSE;
        }
        (*linkedList)->isEqual = isEqual;
        (*linkedList)->freeADT = freeADT;
    } else {
        (*linkedList)->isEqual = NULL;
        (*linkedList)->freeADT = NULL;
    }

    return TRUE;
}


bool LK_isEmpty(LinkedList *linkedList) {
    return linkedList->head == NULL;
}

GENERIC LK_getData(LinkedList *linkedList, unsigned int index) {
    if (linkedList == NULL || index >= linkedList->size) return NULL;

    Node* current = linkedList->head;
    for (unsigned int i = 0; current != NULL && i < index; i++) {
        current = current->next;
    }

    return current != NULL ? current->data : NULL;
}

bool LK_addData(LinkedList *linkedList, GENERIC data) {
    Node *node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return FALSE;

    node->data = data;
    node->next = linkedList->head;
    linkedList->head = node;
    linkedList->size++;
    return TRUE;
}

void LK_freeLinkedList(LinkedList *linkedList) {
    Node* current = linkedList->head;
    while (current != NULL) {
        Node* previous = current;
        current = current->next;

        if (linkedList->dataType == TYPE_ADT && linkedList->freeADT != NULL) {
            linkedList->freeADT(previous->data);
        }

        free(previous);
    }

    linkedList->head = NULL;
    linkedList->size = 0;
}

GENERIC* LK_toArray(LinkedList* linkedList) {
    Node *current = linkedList->head;
    GENERIC* result = (GENERIC*)malloc(sizeof(GENERIC) * linkedList->size);
    if (result == NULL) return NULL;

    for (int i = 0; i < linkedList->size; i++) {
        result[i] = current->data;
        current = current->next;
    }

    return result;
}

bool LK_isDataEqualPRIMITIVE(DataType type, void* data1, void* data2) {
    switch (type) {
        case TYPE_INT: return *((int*)data1) == *((int*)data2);
        case TYPE_FLOAT: return *((float*)data1) == *((float*)data2);
        case TYPE_DOUBLE: return *((double*)data1) == *((double*)data2);
        case TYPE_CHAR: return *((char*)data1) == *((char*)data2);
        case TYPE_SHORT: return *((short*)data1) == *((short*)data2);
        case TYPE_LONG: return *((long*)data1) == *((long*)data2);
        case TYPE_LONGLONG: return *((long long*)data1) == *((long long*)data2);
        default: return FALSE;
    }
}

bool LK_removeDataSEARCH(LinkedList *linkedList, GENERIC data) {
    if (LK_isEmpty(linkedList)) return FALSE;

    Node* current = linkedList->head;
    Node* previous = NULL;

    while (current != NULL) {
        bool equal = (linkedList->dataType != TYPE_ADT) ?
            LK_isDataEqualPRIMITIVE(linkedList->dataType, current->data, data) :
            linkedList->isEqual(current->data, data);

        if (equal) {
            if (previous == NULL) {
                linkedList->head = current->next;
            } else {
                previous->next = current->next;
            }

            if (linkedList->dataType == TYPE_ADT && linkedList->freeADT != NULL) {
                linkedList->freeADT(current->data);
            }

            free(current);
            linkedList->size--;
            return TRUE;
        }

        previous = current;
        current = current->next;
    }

    return FALSE;
}

bool LK_removeDataINDEX(LinkedList *linkedList, unsigned int index) {
    if (linkedList == NULL || index >= linkedList->size) return FALSE;

    Node* current = linkedList->head;
    Node* previous = NULL;

    for (unsigned int i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        linkedList->head = current->next;
    } else {
        previous->next = current->next;
    }

    if (linkedList->dataType == TYPE_ADT && linkedList->freeADT != NULL) {
        linkedList->freeADT(current->data);
    }

    free(current);
    linkedList->size--;

    return TRUE;
}

bool LK_containsData(LinkedList *linkedList, void* data, DataType dataType) {
    Node* current = linkedList->head;

    while (current != NULL) {
        bool equal = (dataType != TYPE_ADT) ?
            LK_isDataEqualPRIMITIVE(dataType, current->data, data) :
            linkedList->isEqual(current->data, data);

        if (equal) return TRUE;
        current = current->next;
    }

    return FALSE;
}

void LK_print(LinkedList *linkedList, void (*ADT_print)(GENERIC)) {
    Node* current = linkedList->head;
    while (current != NULL) {
        ADT_print (current->data);
        current = current->next;
    }
    printf("FIM LISTA\n");
}
