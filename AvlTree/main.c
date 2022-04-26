#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "AvlTree.h"

#define true 1
#define false 0

void printTreeWithLineBreak(AvlTree *root)
{
    printf("\n");
    PrintTreeGraphicaly(root);
    printf("\n");
}

int main()
{
    char *a = "Andre", *b = "Felipe", *c = "Brasil", *d = "Algo";

    AvlTree *root = AvlTreeInit(10, &a, sizeof(char *));
    printTreeWithLineBreak(root);
    root = AvlTreeInsertNode_rec(root, 20, &b, sizeof(char *));
    printTreeWithLineBreak(root);
    root = AvlTreeInsertNode_rec(root, 30, &c, sizeof(char *));
    printTreeWithLineBreak(root);
    root = AvlTreeInsertNode_rec(root, 5, &a, sizeof(char *));
    printTreeWithLineBreak(root);
    root = AvlTreeInsertNode_rec(root, 1, &c, sizeof(char *));
    printTreeWithLineBreak(root);
    root = AvlTreeInsertNode_rec(root, 15, &b, sizeof(char *));
    printTreeWithLineBreak(root);
    root = AvlTreeInsertNode_rec(root, 16, &b, sizeof(char *));
    printTreeWithLineBreak(root);
    root = AvlTreeInsertNode_rec(root, 7, &c, sizeof(char *));
    printTreeWithLineBreak(root);
    root = AvlTreeInsertNode_rec(root, 8, &c, sizeof(char *));
    printTreeWithLineBreak(root);
    root = AvlTreeInsertNode_rec(root, 9, &c, sizeof(char *));
    printTreeWithLineBreak(root);

    // AvlTreePrintTree(root, 0, "%s\n");
    // PrintTreeGraphicaly(root);

    // AvlTree *foundedKey = AvlTreeFindKey_rec(root, 20, NULL);
    // printf("\n\n");
    // // AvlTreePrintTree(foundedKey, 0, "%s\n");
    // PrintTreeGraphicaly(foundedKey);
    // char *myString = NULL;
    // AvlTreeGetData(foundedKey, &myString);
    // printf("\n\n");
    // printf("%s \n", myString);

    // Primeiro caso de remoção
    // AvlTreeRemoveKey_rec(root, 20);
    // PrintTreeGraphicaly(root);
    // printf("\n\n");
    // AvlTreeRemoveKey_rec(root, 16);
    // PrintTreeGraphicaly(root);
    // printf("\n-----------\n");
    // AvlTreeRemoveKey_rec(root, 1);
    // PrintTreeGraphicaly(root);
    // printf("\n-----------\n");
    // AvlTreeRemoveKey_rec(root, 5);
    // PrintTreeGraphicaly(root);
    // printf("\n\n\n");
    // AvlTreePrintTree(root, 0, "%s\n");
    return 0;
}