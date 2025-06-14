#include "read.h"

#include <stdlib.h>

int READ_readShader(const char* shaderPath, char **ptr_str) {
    FILE* shaderFile = fopen(shaderPath, "rb"); // modo binário para evitar problemas de tamanho
    if (!shaderFile) {
        return 0;
    }

    if (fseek(shaderFile, 0, SEEK_END) != 0) {
        fclose(shaderFile);
        return 0;
    }

    long fileSize = ftell(shaderFile);
    if (fileSize == -1L) {
        fclose(shaderFile);
        return 0;
    }

    rewind(shaderFile);

    *ptr_str = (char*)malloc(fileSize + 1);
    if (!*ptr_str) {
        fclose(shaderFile);
        return 0;
    }

    size_t bytesRead = fread(*ptr_str, 1, (size_t)fileSize, shaderFile);
    if (bytesRead != (size_t)fileSize) {
        fclose(shaderFile);
        free(*ptr_str);
        return 0;
    }

    (*ptr_str)[fileSize] = '\0'; // null-terminator

    fclose(shaderFile);
    return 1;
}


