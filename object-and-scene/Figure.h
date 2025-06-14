#ifndef FIGURE_H
#define FIGURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>


typedef struct Figure {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    float *vertices;
    float *indices;

} Figure;

void FIGURE_createRectangleTest(Figure* fig);

#endif //FIGURE_H
