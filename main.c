#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "NYSinterface.h"
#include "file-handling/read.h"
#include "structures/graphs/Tree.h"

//testa lista encadeada para tipos primitvos (INT)
void testeListaEncadeada(void) {
    LinkedList* LK;
    LK_createLinkedList(&LK, TYPE_INT, NULL, NULL);

    int v[] = {1,2,3,4,5};
    GENERIC ptr1 = &v[0];
    GENERIC ptr2 = &v[1];
    GENERIC ptr3 = &v[2];
    GENERIC ptr4 = &v[3];
    GENERIC ptr5 = &v[4];

    LK_addData(LK, ptr1);
    LK_addData(LK, ptr2);
    LK_addData(LK, ptr3);
    LK_addData(LK, ptr4);
    LK_addData(LK, ptr5);

    printf("lista inicial: ");
    for (int i = 0; i < 5; i++) {
        printf("%d -> ", *((int*)LK_getData(LK, i)));
    }
    printf("NULL\n");

    LK_removeDataINDEX(LK, 1);

    printf("lista depois de remocao por index: ");
    for (int i = 0; i < 4; i++) {
        printf("%d -> ", *((int*)LK_getData(LK, i)));
    }
    printf("NULL\n");

    LK_removeDataSEARCH(LK, ptr4);
    printf("lista depois de remocao por busca: ");
    for (int i = 0; i < 3; i++) {
        printf("%d -> ", *((int*)LK_getData(LK, i)));
    }
    printf("NULL\n");

    LK_freeLinkedList(LK);
}

//testa pilha para tipos primitivos (INT)
void testePilha() {
    Stack* pilha;
    STK_createStack(&pilha, TYPE_INT, NULL, NULL);

    int v[] = {1,2,3,4,5};
    GENERIC ptr1 = &v[0];
    GENERIC ptr2 = &v[1];
    GENERIC ptr3 = &v[2];
    GENERIC ptr4 = &v[3];
    GENERIC ptr5 = &v[4];

    STK_push(pilha, ptr1);
    STK_push(pilha, ptr2);
    STK_push(pilha, ptr3);
    STK_push(pilha, ptr4);
    STK_push(pilha, ptr5);
    printf("peek: %d\n\n", *((int*)STK_peek(pilha)));

    puts("pops:");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", *((int*)STK_pop(pilha)));
    }
}

void printInt(GENERIC data) {
    if (data)
        printf("%d", *((int*)data));
    else
        printf("(null)");
}


void testeArvore() {
    Tree* tree;
    int* dataRoot = malloc(sizeof(int));
    *dataRoot = 1;

    if (!TREE_createTree(&tree, "root", TYPE_INT, NULL)) {
        printf("Erro ao criar a árvore.\n");
    }

    TREE_addDataToNode(tree, "root", dataRoot);

    // Adiciona 4 filhos em diferentes níveis
    TREE_addNode(tree, "root", "a");
    TREE_addNode(tree, "root", "b");
    TREE_addNode(tree, "root/a", "c");
    TREE_addNode(tree, "root/a", "d");

    int* valA = malloc(sizeof(int)); *valA = 10;
    int* valB = malloc(sizeof(int)); *valB = 20;
    int* valC = malloc(sizeof(int)); *valC = 30;
    int* valD = malloc(sizeof(int)); *valD = 40;

    TREE_addDataToNode(tree, "root/a", valA);
    TREE_addDataToNode(tree, "root/b", valB);
    TREE_addDataToNode(tree, "root/a/c", valC);
    TREE_addDataToNode(tree, "root/a/d", valD);

    printf("Árvore de inteiros:\n");
    TREE_print(tree, 0, printInt);

    // Liberar a árvore se tiver função TREE_free
     TREE_freeTree(tree);
}

void testeInterface() {
    PROJECT project;
    if (!NYS_createProject(&project, "teste")) {
        printf("NYS_createProject() failed\n");
        NYS_print(project);
    }


    NYS_createScene(project, "ROOT-teste", "cena1");
    NYS_print(project);
    NYS_addObjectToScene(project, "ROOT-teste", "cena1", "object1",
        0.5f, 0.5f, 0.0f, 0.0f);

    NYS_print(project);
}

int main(void) {
    testeInterface();


    return 0;
}

