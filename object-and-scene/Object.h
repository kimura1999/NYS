#ifndef OBJECT_H
#define OBJECT_H

#include "../structures/macros.h"
#include "Figure.h"

typedef struct Object Object;

bool OBJECT_createObject(Object** ptr_obj, char* name, float width, float heigth, float posX, float posY);

void OBJECT_freeObject(void* ptr_object);

bool OBJECT_isEqual(void* data1, void* data2);

GENERIC OBJECT_getPtr();

char* OBJECT_getName(Object* object);

Figure* OBJECT_getFigure(Object* object);

void OBJECT_print(Object* object);

#endif //OBJECT_H
