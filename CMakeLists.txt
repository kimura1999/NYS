cmake_minimum_required(VERSION 3.31)
project(NYS C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(extern/glfw)

include_directories(
        extern/glfw/include
        extern/glad/include
)

file(GLOB GLAD_SRC extern/glad/src/*.c)

add_executable(NYS main.c ${GLAD_SRC}
        object-and-scene/graphics.c
        object-and-scene/graphics.h
        object-and-scene/Scene.c
        object-and-scene/Scene.h
        object-and-scene/Object.c
        object-and-scene/Object.h
        structures/lists/LinkedList.c
        structures/lists/LinkedList.h
        object-and-scene/SceneManager.c
        object-and-scene/SceneManager.h
        structures/stacks/Stack.c
        structures/stacks/Stack.h
        NYSinterface.c
        NYSinterface.h
        file-handling/read.c
        file-handling/read.h
        structures/macros.h
        structures/graphs/Tree.c
        structures/graphs/Tree.h
        object-and-scene/Figure.h
        object-and-scene/Figure.c
)

target_link_libraries(NYS glfw opengl32)
