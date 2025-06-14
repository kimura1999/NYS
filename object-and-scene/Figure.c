#include "Figure.h"

void FIGURE_createRectangleTest(Figure* figure) {
    float vertices[] = {
        // x, y
        0.5f,  0.5f,  // topo direito
        0.5f, -0.5f,  // baixo direito
       -0.5f, -0.5f,  // baixo esquerdo
       -0.5f,  0.5f   // topo esquerdo
   };

    unsigned int indices[] = {
        0, 1, 3,  // primeiro triângulo
        1, 2, 3   // segundo triângulo
    };

    glGenVertexArrays(1, &figure->VAO);
    glGenBuffers(1, &figure->VBO);
    glGenBuffers(1, &figure->EBO);

    // vincula VAO
    glBindVertexArray(figure->VAO);

    // vincula e preenche VBO
    glBindBuffer(GL_ARRAY_BUFFER, figure->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // vincula e preenche EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, figure->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // configura o atributo do vertex shader
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // desvincula tudo (boa prática)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}
