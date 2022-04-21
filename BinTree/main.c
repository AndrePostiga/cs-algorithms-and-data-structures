#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "BinarySearchTree.h"

#define true 1
#define false 0

int main()
{
    char *a = "Andre", *b = "Felipe", *c = "Brasil", *d = "Algo";

    BinarySearchTree *root = BinarySearchTreeInit(10, &a, sizeof(char *));
    BinarySearchInsertNode_rec(root, 20, &b, sizeof(char *));
    BinarySearchInsertNode_rec(root, 30, &c, sizeof(char *));
    BinarySearchInsertNode_rec(root, 5, &a, sizeof(char *));
    BinarySearchInsertNode_rec(root, 1, &c, sizeof(char *));
    BinarySearchInsertNode_rec(root, 15, &b, sizeof(char *));
    BinarySearchInsertNode_rec(root, 16, &b, sizeof(char *));
    BinarySearchInsertNode_rec(root, 7, &c, sizeof(char *));
    BinarySearchInsertNode_rec(root, 8, &c, sizeof(char *));
    BinarySearchInsertNode_rec(root, 9, &c, sizeof(char *));

    // BinarySearchTreePrintTree(root, 0, "%s\n");
    PrintTreeGraphicaly(root);

    // BinarySearchTree *foundedKey = BinarySearchTreeFindKey_rec(root, 20, NULL);
    // printf("\n\n");
    // // BinarySearchTreePrintTree(foundedKey, 0, "%s\n");
    // PrintTreeGraphicaly(foundedKey);
    // char *myString = NULL;
    // BinarySearchTreeGetData(foundedKey, &myString);
    // printf("\n\n");
    // printf("%s \n", myString);

    // Primeiro caso de remoção
    BinarySearchTreeRemoveKey_rec(root, 20);
    PrintTreeGraphicaly(root);
    printf("\n\n");
    BinarySearchTreeRemoveKey_rec(root, 16);
    PrintTreeGraphicaly(root);
    printf("\n-----------\n");
    BinarySearchTreeRemoveKey_rec(root, 1);
    PrintTreeGraphicaly(root);
    printf("\n-----------\n");
    BinarySearchTreeRemoveKey_rec(root, 5);
    PrintTreeGraphicaly(root);
    printf("\n\n\n");
    // BinarySearchTreePrintTree(root, 0, "%s\n");
    return 0;
}