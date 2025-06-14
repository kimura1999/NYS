#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../structures/stacks/Stack.h"

#include "Object.h"
#include "Scene.h"

typedef struct SceneManager SceneManager;

void SCENEMANAGER_freeSceneManager(void* ptr_sceneManager);

bool SCENEMANAGER_createSceneManager(SceneManager **ptr_sceneManager, const char* name);

bool SCENEMANAGER_addScene(SceneManager* sceneManager, char* locationPath, Scene* scene);

bool SCENEMANAGER_removeScene(SceneManager* sceneManager, char* locationPath);

Scene* SCENEMANAGER_getScene(SceneManager* sceneManager, char* locationPath);

void SCENEMANAGER_print(SceneManager* sceneManager);

#endif //SCENEMANAGER_H
