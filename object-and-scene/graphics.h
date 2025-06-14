#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SceneManager.h"

int graphics_start(const char* vertexShaderSource, const char* fragmentShaderSource, int width, int height, SceneManager* sceneManager);

#endif //GRAPHICS_H
