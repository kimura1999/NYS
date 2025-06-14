#include "Object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Object {
    char name[64];
    float width, heigth;
    float posX, posY;

    Figure* figure;
} Object;

bool OBJECT_createObject(Object** ptr_obj, char* name, float width, float heigth, float posX, float posY) {
    *ptr_obj = malloc(sizeof(Object));
    if (*ptr_obj == NULL) return FALSE;

    strcpy((*ptr_obj)->name, name);
    (*ptr_obj)->name[strlen(name) - 1] = '\0';

    (*ptr_obj)->width = width;
    (*ptr_obj)->heigth = heigth;

    (*ptr_obj)->posX = posX;
    (*ptr_obj)->posY = posY;

    return TRUE;
}

void OBJECT_freeObject(void* ptr_object) {
    free(((Object*)ptr_object)->figure);
    free(ptr_object);
}

bool OBJECT_isEqual(void* data1, void* data2) {
    Object* ptr_obj1 = ((Object*)data1);
    Object* ptr_obj2 = ((Object*)data2);

    return ptr_obj1->width == ptr_obj2->width &&
        ptr_obj1->posX == ptr_obj2->posX && ptr_obj1->posY == ptr_obj2->posY &&
            strcmp(ptr_obj1->name, ptr_obj2->name) == 0;
}

GENERIC OBJECT_getPtr() {
    return malloc(sizeof(Object));
}

char* OBJECT_getName(Object* object) {
    return object->name;
}

Figure* OBJECT_getFigure(Object* object) {
    return object->figure;
}

void OBJECT_print(Object* object) {
    printf("[\n\tName: %s\n", object->name);
    printf("\tWidth: %f\n", object->width);
    printf("\tHeigth: %f\n", object->heigth);
    printf("\tPosX: %f\n", object->posX);
    printf("\tPosY: %f\n]", object->posY);

}