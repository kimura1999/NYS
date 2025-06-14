#ifndef NYSINTERFACE_H
#define NYSINTERFACE_H

#include "./object-and-scene/graphics.h"
#include "file-handling/read.h"

typedef struct project* PROJECT;

bool NYS_createProject(PROJECT *proj, char* name);

bool NYS_createScene(PROJECT proj, char* locationPath, char* sceneName);

bool NYS_addObjectToScene(PROJECT proj, char* scenePath, char* objectPath,
    char* objectName, float width, float height, float posX, float posY);

bool NYS_start(PROJECT proj);

void NYS_print(PROJECT proj);

#endif //NYSINTERFACE_H
