#include "Tree.h"

typedef struct Tree {
    char name[256];
    GENERIC data;
    LinkedList* children; //Type: TREE
    DataType dataType;
    struct Tree* father;

    void (*freeData)(GENERIC);
} Tree;

bool TREE_isRoot(Tree* tree) {
    return tree->father == NULL;
}

bool TREE_isLeaf(Tree* tree) {
    return LK_getSize(tree->children) == 0;
}

char* TREE_substring(char* string, unsigned int start, unsigned int length) {
    if (!string) return NULL;

    unsigned int str_len = strlen(string);

    if (start >= str_len) return NULL;

    if (start + length > str_len) {
        length = str_len - start;
    }

    char* substring = (char*)malloc(length + 1);
    if (!substring) return NULL;

    strncpy(substring, string + start, length);
    substring[length] = '\0';

    return substring;
}

bool TREE_isEqual(GENERIC a, GENERIC b) {
    char* A = TREE_getPath((Tree*)a);
    char* B = TREE_getPath((Tree*)b);

    char strA[strlen(A) + 1]; strcpy(strA,A);
    char strB[strlen(B) + 1]; strcpy(strB,B);

    free(A); free(B);

    return strcmp(strA, strB) == 0;
}

bool TREE_createTree(Tree **tree, const char* name, DataType dataType, void (*freeData)(GENERIC)) {
    *tree = (Tree*)malloc(sizeof(Tree));
    if (*tree == NULL) {
        return FALSE;
    }
    (*tree)->dataType = dataType;
    (*tree)->data = NULL;
    strcpy((*tree)->name, name);
    (*tree)->father = NULL;
    (*tree)->freeData = freeData;

    if (!LK_createLinkedList(&(*tree)->children, dataType, TREE_isEqual, freeData)) {
        free(*tree);
        *tree = NULL;
        return FALSE;
    }

    return TRUE;
}

bool TREE_isEmpty(Tree *tree) {
    return tree == NULL || tree->data == NULL;
}

char* TREE_getpathRecursive(Tree* tree, char* buildingPath) {
    if (tree->father == NULL) {
        return buildingPath;
    }

    char temp[1024];
    snprintf(temp, sizeof(temp), "%s/%s", tree->father->name, buildingPath);
    if (strlen(temp) >= 1024) return buildingPath;

    strcpy(buildingPath, temp);
    return TREE_getpathRecursive(tree->father, buildingPath);
}

char* TREE_getPath(Tree *tree) {
    if (tree == NULL) return NULL;

    char* buildingPath = malloc(1024);
    if (!buildingPath) return NULL;

    strcpy(buildingPath, tree->name);
    return TREE_getpathRecursive(tree, buildingPath);
}

char* TREE_getName(Tree *tree) {
    return tree->name;
}

Tree* TREE_getChild(Tree* tree, char* childPath) {
    for (unsigned int i = 0; i < LK_getSize(tree->children); i++) {
        if (strcmp(((Tree*)LK_getData(tree->children, i))->name, childPath) == 0) {
            return (Tree*)LK_getData(tree->children, i);
        }
    }
    return NULL;
}

int TREE_indexOfFirstSlash(const char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '/') return i;
    }
    return strlen(string);
}


int TREE_indexOfLastSlash(const char* string) {
    int i = strlen(string) - 1;
    while (i >= 0 && string[i] != '/') {
        i--;
    }
    return (i >= 0) ? i : -1;
}

int TREE_indexOfSecondSlash(const char* string) {
    bool foundOneSlash = FALSE;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '/')
            if (!foundOneSlash) foundOneSlash = TRUE;
            else return i;
    }
    return strlen(string);
}

int TREE_indexOfNumberSlash(const char* string, int num) {
    int slashes = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == '/')
            slashes++;
        if (slashes == num) return i;
    }
    return strlen(string);
}

Tree* TREE_visitNodeRecursive(Tree *tree, const char *locationPath, int s, int e) {
    char* currentPath = TREE_getPath(tree);

    if (strcmp(currentPath, locationPath) == 0) {
        free(currentPath);
        return tree;
    }

    if (TREE_isLeaf(tree)) return NULL;

    int start = TREE_indexOfNumberSlash(locationPath, s) + 1;
    int end = TREE_indexOfNumberSlash(locationPath, e);
    int length = end - start;

    char* nextNodeName = TREE_substring(locationPath, start, length);
    if (!nextNodeName) return NULL;

    Tree* returnNode = NULL;
    for (unsigned int i = 0; i < LK_getSize(tree->children); i++) {
        Tree* child = (Tree*)LK_getData(tree->children, i);
        if (strcmp(nextNodeName, child->name) == 0) {
            returnNode = TREE_visitNodeRecursive(child, locationPath, ++s, ++e);
            break;
        }
    }

    free(nextNodeName);
    free(currentPath);

    return returnNode;
}

Tree* TREE_visitNode(Tree *tree, const char *locationPath) {
    Tree* node = TREE_visitNodeRecursive(tree, locationPath, 1, 2);

    return node;
}

bool TREE_addNode(Tree *tree, char* locationPath, const char* name) {
    Tree* node = TREE_visitNode(tree, locationPath);
    puts("oiiiii");
    if (node == NULL) return FALSE;
    Tree* newNode;
    if (!TREE_createTree(&newNode, name, tree->dataType, tree->freeData)) return FALSE;

    newNode->father = node;

    if (!LK_addData(node->children, newNode)) {
        if (tree->freeData != NULL) tree->freeData(newNode->data);
        free(newNode);
        return FALSE;
    }

    return TRUE;
}

void TREE_freeTree(Tree *tree) {
    if (tree == NULL) return;
    if (tree->children == NULL) return;

    for (int i = 0; i < LK_getSize((tree->children)); i++) {
        TREE_freeTree(LK_getData(tree->children, i));
    }

    LK_freeLinkedList(tree->children);

    free(tree);
    tree = NULL;
}

bool TREE_removeNode(Tree* tree, char* locationPath) {
    Tree* node;
    if (!((node = TREE_visitNode(tree, locationPath)))) return FALSE;



    Tree* father = node->father;

    for (int i = 0; i < LK_getSize(father->children); i++) {
        if (LK_getData(father->children, i) == node) {
            LK_removeDataINDEX(father->children, i);
            return TRUE;
        }
    }
    return FALSE;
}

bool TREE_addDataToNode(Tree* tree, char* locationPath, GENERIC data) {
    Tree* node = TREE_visitNode(tree, locationPath);
    if (node == NULL) return FALSE;

    if (node->data != NULL && tree->freeData != NULL) {
        tree->freeData(node->data);
        free(node->data);
    }

    node->data = data;
    return TRUE;
}


bool TREE_addNodeAndData(Tree* tree, char* locationPath, GENERIC data, const char* name) {
    return TREE_addNode(tree, locationPath, name) &&
        TREE_addDataToNode(tree, strcat(locationPath,strcat("/", name)), data);

}

GENERIC TREE_getNodeData(Tree* tree, char* locationPath) {
    Tree* node = TREE_visitNode(tree, locationPath);
    if (node == NULL) return FALSE;

    return node->data;
}

void TREE_printPath(Tree* node) {
    if (node == NULL) return;

    if (node->father != NULL) {
        TREE_printPath(node->father);
        printf("/%s", node->name);
    } else {
        printf("/%s", node->name); // raiz
    }
}

void TREE_print(Tree* tree, int level, void (*printADT)(GENERIC)) {
    if (tree == NULL) return;

    // Indentação conforme o nível
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    // Caminho completo até o nó
    printf("- ");
    TREE_printPath(tree);

    // Endereço do nó
    printf(" (endereco: %p)", (void*)tree);

    // Dado armazenado no nó
    if (tree->data != NULL) {
        printf(" : ");
        if (tree->dataType == TYPE_ADT) {
            if (printADT != NULL) {
                printADT(tree->data);
            } else {
                printf("[ADT - sem funcao de impressao]");
            }
        } else {
            // Impressão dos tipos primitivos conhecidos
            switch (tree->dataType) {
                case TYPE_INT:
                    printf("%d", *((int*)tree->data));
                    break;
                case TYPE_FLOAT:
                    printf("%.2f", *((float*)tree->data));
                    break;
                default:
                    printf("[tipo desconhecido]");
                    break;
            }
        }
    } else {
        printf(" : (sem dado)");
    }

    printf("\n");

    // Imprime os filhos recursivamente
    unsigned int size = LK_getSize(tree->children);
    for (unsigned int i = 0; i < size; i++) {
        Tree* child = (Tree*)LK_getData(tree->children, i);
        TREE_print(child, level + 1, printADT);
    }
}

int TREE_getSize(Tree* tree) {
    if (TREE_isLeaf(tree)) return 1;

    int size = 0;
    for (int i = 0; i < LK_getSize(tree->children); i++) {
        size += 1 + TREE_getSize(LK_getData(tree->children, i));
    }

    return size;
}

void recursiveTreeToArray(Tree* tree, GENERIC* array, int i) {
    array[i] = tree->data;
    i++;
    if (TREE_isLeaf(tree)) {
        return;
    }

    for (; i < LK_getSize(tree->children);) {
        array[i] = LK_getData(tree->children, i);
        i++;
        recursiveTreeToArray(tree, array, i);
    }
}

GENERIC* TREE_toArray(Tree* tree) {
    GENERIC* array = (GENERIC*) malloc(sizeof(GENERIC) * TREE_getSize(tree));
    if (array == NULL) return NULL;

    recursiveTreeToArray(tree, array, 0);

    return array;
}