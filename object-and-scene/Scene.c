#include "Scene.h"
#include <stdlib.h>
#include <string.h>

typedef struct Scene {
    char *name;
    Tree* objects;
} Scene;

char* SCENE_getSceneName(Scene* scene) {
    return scene->name;
}

Tree* SCENE_getSceneObjects(Scene* scene) {
    return scene->objects;
}

bool SCENE_createScene(Scene** scene, const char *name){
    *scene = (Scene*)malloc(sizeof(Scene));
    if (*scene == NULL) {
        return FALSE;
    }

    if (!TREE_createTree(&(*scene)->objects, name, TYPE_ADT, OBJECT_freeObject)) {
        return FALSE;
    }


    (*scene)->name = malloc(strlen(name) * sizeof(char) + 1);
    strcpy((*scene)->name, name);

    return TRUE;
}

void SCENE_freeScene(GENERIC scene) {
    TREE_freeTree(&((Scene*)scene)->objects);
    free(((Scene*)scene)->name);
    free(scene);
}

bool SCENE_addObject(Scene* scene, char* locationPath, Object* object) {
    if (!TREE_addNode(scene->objects, locationPath, OBJECT_getName(object))) {
        return FALSE;
    }

    int sizeOfPath = strlen(locationPath) * sizeof(char) + 1 +
        strlen(OBJECT_getName(object)) * sizeof(char) + 1;

    char* path = malloc(sizeOfPath);
    if (path == NULL) {
        return FALSE;
    }

    snprintf(path, sizeOfPath, "%s/%s", locationPath, OBJECT_getName(object));

    if (!TREE_addDataToNode(scene->objects, path, object)) {
        TREE_removeNode(scene->objects, path);
        free(path);
        return FALSE;
    }

    free(path);
    return TRUE;
}

bool SCENE_isEqual(void* scene1, void* scene2) {
    return ((Scene*)scene1)->objects == ((Scene*)scene2)->objects;
}

bool SCENE_removeObjectSEARCH(Scene* scene, char* locationPath) {
    return TREE_removeNode(scene->objects, locationPath);
}

Object* SCENE_getObject(Scene* scene, char* locationPath) {
    return TREE_getNodeData(scene->objects, locationPath);
}

GENERIC SCENE_getPtr() {
    return malloc(sizeof(Scene));
}

int SCENE_getObjectsquantity(Scene* scene) {
    return TREE_getSize(scene->objects);
}

Object** SCENE_getArrayObjects(Scene* scene) {
    return (Object**)TREE_toArray(scene->objects);
}

void SCENE_print(Scene* scene) {
    printf("scene name: %s\n", scene->name);

    TREE_print(scene->objects, 0, OBJECT_print);
}
