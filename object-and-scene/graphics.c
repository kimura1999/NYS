#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "SceneManager.h"

void graphics_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void graphics_processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int graphics_compileVertexShader(const char* vertexShaderSource, unsigned int* vertexShader){
    *vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(*vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(*vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(*vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "Vertex Shader Compilation Failed:\n%s\n", infoLog);
        return 0;
    }
    return 1;
}

int graphics_compileFragmentShader(const char* fragmentShaderSource, unsigned int* fragmentShader) {
    *fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(*fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(*fragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(*fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "Fragment Shader Compilation Failed:\n%s\n", infoLog);
        return 0;
    }
    return 1;
}

int graphics_createProgram(unsigned int vertexShader, unsigned int fragmentShader, unsigned int* shaderProgram) {
    *shaderProgram = glCreateProgram();
    glAttachShader(*shaderProgram, vertexShader);
    glAttachShader(*shaderProgram, fragmentShader);
    glLinkProgram(*shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(*shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "Shader Program Linking Failed:\n%s\n", infoLog);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return 1;
}

void graphics_showScene(Scene *scene) {
    Object** obj = SCENE_getArrayObjects(scene);
    int count = SCENE_getObjectsquantity(scene);

    for (int i = 0; i < count; i++) {
        if (obj[i] != NULL) {
            Figure* fig = OBJECT_getFigure(obj[i]);
            FIGURE_createRectangleTest(fig);
            if (fig != NULL) {
                glBindVertexArray(fig->VAO);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }
    }

    glBindVertexArray(0);
}


int graphics_start(const char* vertexShaderSource, const char* fragmentShaderSource, int width, int height, SceneManager* sceneManager) {
    if (!glfwInit()) return 0;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        return 0;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, graphics_framebuffer_size_callback);

    unsigned int vertexShader;
    if (!graphics_compileVertexShader(vertexShaderSource, &vertexShader)) {
        glfwTerminate();
        return 0;
    }

    unsigned int fragmentShader;
    if (!graphics_compileFragmentShader(fragmentShaderSource, &fragmentShader)) {
        glDeleteShader(vertexShader);
        glfwTerminate();
        return 0;
    }

    unsigned int shaderProgram;
    if (!graphics_createProgram(vertexShader, fragmentShader, &shaderProgram)) {
        glfwTerminate();
        return 0;
    }

    //render loop
    while (!glfwWindowShouldClose(window)) {
        graphics_processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        Scene* scene = SCENEMANAGER_getScene(sceneManager, "ROOT-teste");
        if (scene) {
            graphics_showScene(scene);
            puts("showScene() called");
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 1;
}
