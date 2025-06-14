#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../lists/LinkedList.h"

#define TREE_ROOT NULL

typedef struct Tree Tree;

bool TREE_isRoot(Tree* tree);

bool TREE_createTree(Tree **tree, const char* name, DataType dataType, void (*freeData)(GENERIC));

bool TREE_isEmpty(Tree *tree);

char* TREE_getPath(Tree *tree);

char* TREE_getName(Tree *tree);

Tree* TREE_getChild(Tree* tree, char* childPath);

Tree* TREE_visitNode(Tree *tree, const char *locationPath);

bool TREE_addNode(Tree *tree, char* locationPath, const char* name);

void TREE_freeTree(Tree *tree);

bool TREE_addDataToNode(Tree* tree, char* locationPath, void* data);

GENERIC TREE_getNodeData(Tree* tree, char* locationPath);

bool TREE_removeNode(Tree* tree, char* locationPath);

void TREE_print(Tree* tree, int level, void (*printData)(GENERIC));

int TREE_getSize(Tree* tree);

GENERIC* TREE_toArray(Tree* tree);

#endif //GRAPH_H
