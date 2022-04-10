#include "stdlib.h"
#include "stdio.h"
#include "BinaryTree.h"

#define true 1
#define false 0

Tree *BinaryTreeInit(void *data, int typeSizeOfData)
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->typeSizeOf = typeSizeOfData;
    tree->left = NULL;
    tree->right = NULL;

    if (data != NULL)
    {
        tree->data = malloc(typeSizeOfData);
        memcpy(tree->data, data, typeSizeOfData);
    }
    else
    {
        tree->data = NULL;
    }

    return tree;
}

int BinaryTreeGetData(Tree *tree, void *memoryAddress)
{
    if (tree == NULL)
        return false;

    memcpy(memoryAddress, tree->data, tree->typeSizeOf);

    return true;
}

void BinaryTreePrintTree(Tree *root, int tabSize, char *pattern)
{
    for (int i = 0; i < tabSize; i++)
    {
        printf("-");
    }

    if (root != NULL)
    {
        if (strstr(pattern, "%c") != NULL)
        {
            printf(pattern, *(char *)root->data);
        }
        else if (strstr(pattern, "%d") != NULL || strstr(pattern, "%i") != NULL || strstr(pattern, "%u") != NULL)
        {
            printf(pattern, *(int *)root->data);
        }
        else if (strstr(pattern, "%s") != NULL)
        {
            printf(pattern, *(char **)root->data);
        }
        else if (strstr(pattern, "f") != NULL)
        {
            printf(pattern, *(double *)root->data);
        }
        else
        {
            printf("%p\n", root->data);
        }

        BinaryTreePrintTree(root->left, tabSize + 2, pattern);
        printf("\n");
        BinaryTreePrintTree(root->right, tabSize + 2, pattern);
    }
    else
    {
        printf("NULL");
    }
}