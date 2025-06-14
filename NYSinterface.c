#include "NYSinterface.h"
#include "file-handling/read.h"
#include <string.h>
#include <stdlib.h>

typedef struct project {
    char name[256];
    SceneManager *sceneManager;
    LinkedList *objects;
    LinkedList *scenes;
} project;

typedef project* PROJECT;

bool NYS_createProject(PROJECT *proj, char* name) {
    if (proj == NULL || name == NULL) return FALSE;

    *proj = (PROJECT)malloc(sizeof(project));
    if (*proj == NULL) return FALSE;

    char prefixedName[256];
    snprintf(prefixedName, sizeof(prefixedName), "ROOT-%s", name);

    if (!SCENEMANAGER_createSceneManager(&(*proj)->sceneManager, prefixedName)) {
        free(*proj);
        *proj = NULL;
        return FALSE;
    }

    if (!LK_createLinkedList(&(*proj)->objects, TYPE_ADT, OBJECT_isEqual, OBJECT_freeObject)) {
        SCENEMANAGER_freeSceneManager((*proj)->sceneManager);
        free(*proj);
        *proj = NULL;
        return FALSE;
    }

    if (!LK_createLinkedList(&(*proj)->scenes, TYPE_ADT, SCENE_isEqual, SCENE_freeScene)) {
        LK_freeLinkedList((*proj)->objects);
        SCENEMANAGER_freeSceneManager(&(*proj)->sceneManager);
        free(*proj);
        *proj = NULL;
        return FALSE;
    }


    strcpy((*proj)->name, name);

    return TRUE;
}


bool NYS_createScene(PROJECT proj, char* locationPath, char* sceneName) {
    Scene* scene;

    if (!SCENE_createScene(&scene, sceneName)) {
        return FALSE;
    }

    if (!LK_addData(proj->scenes, scene)) {
        SCENE_freeScene(scene);
        return FALSE;
    }

    if (!SCENEMANAGER_addScene(proj->sceneManager, locationPath, scene)) {
        SCENE_freeScene(&scene);
        LK_removeDataSEARCH(proj->scenes, scene);
        return FALSE;
    }

    return TRUE;
}

bool NYS_addObjectToScene(PROJECT proj, char* scenePath, char* objectPath,
    char* objectName, float width, float height, float posX, float posY) {

    Object* ptrObject;
    if(!OBJECT_createObject(&ptrObject, objectName, width, height, posX, posY)) {
        return FALSE;
    }

    if (!LK_addData(proj->objects, ptrObject)) {
        OBJECT_freeObject(ptrObject);
        return FALSE;
    }
    puts("oiiiii");
    if(!SCENE_addObject(SCENEMANAGER_getScene(proj->sceneManager, scenePath), objectPath, ptrObject)) {
        OBJECT_freeObject(ptrObject);
        return FALSE;
    }

    return TRUE;
}

bool NYS_start(PROJECT proj) {
    char* vertexShader;
    READ_readShader("../shaders/vertex-shaders/vertexShader.txt", &vertexShader);

    char* fragmentShader;
    READ_readShader("../shaders/fragment-shaders/fragmentShader.txt", &fragmentShader);
    return graphics_start(vertexShader, fragmentShader, 800, 800, proj->sceneManager);
}

void NYS_print(PROJECT proj) {
    printf("NYS_printProject() called\n");
    printf("PROJECT_NAME: %s\n", proj->name);

    SCENEMANAGER_print(proj->sceneManager); puts("");
    LK_print(proj->objects, OBJECT_print); puts("");
    LK_print(proj->scenes, SCENE_print); puts("");


}