#include "stdlib.h"
#include "stdio.h"
#include "BinaryTree.h"

#define true 1
#define false 0

int main()
{
    char *a = "Andre", *b = "Felipe", *c = "Brasil", *d = "Algo";

    Tree *root = BinaryTreeInit(&a, sizeof(char *));
    root->left = BinaryTreeInit(&b, sizeof(char *));
    root->right = BinaryTreeInit(&c, sizeof(char *));

    root->right->left = BinaryTreeInit(&d, sizeof(char *));

    BinaryTreePrintTree(root, 0, "%s\n");
    printf("\n\n\n%d\n", CheckFullTree_rec(root));
    return 0;
}