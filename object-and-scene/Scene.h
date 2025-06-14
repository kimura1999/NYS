#ifndef SCENE_H
#define SCENE_H

#include "../structures/lists/LinkedList.h"
#include "../structures/graphs/Tree.h"

#include "Object.h"

typedef struct Scene Scene;

char* SCENE_getSceneName(Scene* scene);

Tree* SCENE_getSceneObjects(Scene* scene);

bool SCENE_createScene(Scene** scene, const char *name);

void SCENE_freeScene(void* scene);

bool SCENE_addObject(Scene* scene, char* locationPath, Object* data);

bool SCENE_isEqual(void* scene1, void* scene2);

bool SCENE_removeObjectSEARCH(Scene* scene, char* locationPath);

Object* SCENE_getObject(Scene* scene, char* locationPath);

GENERIC SCENE_getPtr();

int SCENE_getObjectsquantity(Scene* scene);

Object** SCENE_getArrayObjects(Scene* scene);

void SCENE_print(Scene* scene);

#endif //SCENE_H
