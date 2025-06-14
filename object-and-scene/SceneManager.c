#include "SceneManager.h"

typedef struct SceneManager {
    Tree *SceneTree;
} SceneManager;

void SCENEMANAGER_freeSceneManager(void* ptrSceneManager) {
    SceneManager* sceneManager = (SceneManager*) ptrSceneManager;
    TREE_freeTree(&sceneManager->SceneTree);
    free(sceneManager);
}

bool SCENEMANAGER_createSceneManager(SceneManager **ptr_sceneManager, const char* name) {
    *ptr_sceneManager = (SceneManager*) malloc(sizeof(SceneManager));
    if (*ptr_sceneManager == NULL) {
        return FALSE;
    }

    if (!TREE_createTree(&(*ptr_sceneManager)->SceneTree, name, TYPE_ADT, SCENE_freeScene)) {
        free(*ptr_sceneManager);
        *ptr_sceneManager = NULL;
        return FALSE;
    }

    return TRUE;

}

bool SCENEMANAGER_addScene(SceneManager* sceneManager, char* locationPath, Scene* scene) {
    char* sceneName = SCENE_getSceneName(scene);

    int size = snprintf(NULL, 0, "%s/%s", locationPath, sceneName) + 1;
    char* scenePath = (char*)malloc(size);
    if (!scenePath) {
        return FALSE;
    }
    snprintf(scenePath, size, "%s/%s", locationPath, sceneName);

    if (!TREE_addNode(sceneManager->SceneTree, locationPath, sceneName)) {
        free(scenePath);
        return FALSE;
    }

    if (!TREE_addDataToNode(sceneManager->SceneTree, scenePath, scene)) {
        TREE_removeNode(sceneManager->SceneTree, scenePath);
        free(scenePath);
        return FALSE;
    }

    free(scenePath);
    return TRUE;
}



bool SCENEMANAGER_removeScene(SceneManager* sceneManager, char* locationPath) {
    return TREE_removeNode(sceneManager->SceneTree, locationPath);
}

Scene* SCENEMANAGER_getScene(SceneManager* sceneManager, char* locationPath) {
    return (Scene*) TREE_getNodeData(sceneManager->SceneTree, locationPath);
}

void SCENEMANAGER_print(SceneManager* sceneManager) {
    TREE_print(sceneManager->SceneTree, 0, SCENE_print);
}