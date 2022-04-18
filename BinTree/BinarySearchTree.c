#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "BinarySearchTree.h"

#define true 1
#define false 0

BinarySearchTree *BinarySearchTreeRemoveKey(BinarySearchTree *tree, int key);
int BinarySearchTreeGetData(BinarySearchTree *tree, void *memoryAddress);

BinarySearchTree *BinarySearchTreeInit(int key, void *data, int typeSizeOfData)
{
    BinarySearchTree *newNode = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));
    newNode->key = key;
    newNode->typeSizeOf = typeSizeOfData;
    newNode->left = NULL;
    newNode->right = NULL;

    if (data != NULL)
    {
        newNode->data = malloc(typeSizeOfData);
        memcpy(newNode->data, data, typeSizeOfData);
    }
    else
    {
        newNode->data = NULL;
    }

    return newNode;
}

BinarySearchTree *BinarySearchInsertNode(BinarySearchTree *tree, int key, void *data, int typeSizeOfData)
{
    BinarySearchTree *newNode;
    if (tree == NULL)
    {
        return BinarySearchTreeInit(key, data, typeSizeOfData);
    }
    else
    {
        newNode = BinarySearchTreeInit(key, data, tree->typeSizeOf);
    }

    BinarySearchTree *temp = tree;
    BinarySearchTree *previous = tree;
    while (temp != NULL) // a inserção é feita sempre nas folhas, por isso do while até achar uma folha
    {
        previous = temp;
        if (key < temp->key) // se for maior que a raiz
            temp = temp->left;
        else if (key > temp->key) // se for menor que a raiz
            temp = temp->right;
        else if (key == temp->key) // se for igual não pode permitir
        {
            printf("Inserção inválida! "); // chave já existe
            exit(1);
        }
    }

    if (key < previous->key)
        previous->left = newNode;
    else
        previous->right = newNode;

    return tree;
}

BinarySearchTree *BinarySearchInsertNode_rec(BinarySearchTree *tree, int key, void *data, int typeSizeOfData)
{
    if (tree == NULL)
    {
        return BinarySearchTreeInit(key, data, typeSizeOfData);
    }
    else
    {
        if (key < tree->key)
            tree->left = BinarySearchInsertNode_rec(tree->left, key, data, typeSizeOfData);
        else if (key > tree->key)
            tree->right = BinarySearchInsertNode_rec(tree->right, key, data, typeSizeOfData);
        else
        {
            printf("Inserção inválida! "); // chave já existe
            exit(1);
        }
    }

    return tree;
}

BinarySearchTree *BinarySearchTreeFindKey(BinarySearchTree *tree, int key, BinarySearchTree **parent)
{
    while (tree != NULL)
    {
        if (key == tree->key)
            return tree;

        *parent = tree;

        if (key < tree->key)
            tree = tree->left;
        else if (key > tree->key)
            tree = tree->right;
    }

    return NULL;
}

BinarySearchTree *BinarySearchTreeFindKey_rec(BinarySearchTree *tree, int key, BinarySearchTree **parent)
{
    if (tree == NULL)
        return NULL;

    if (key == tree->key)
        return tree;

    if (parent != NULL)
        *parent = tree;

    if (key < tree->key)
        return BinarySearchTreeFindKey_rec(tree->left, key, parent);
    else if (key > tree->key)
        return BinarySearchTreeFindKey_rec(tree->right, key, parent);

    return NULL;
}

int BinarySearchTreeGetData(BinarySearchTree *tree, void *memoryAddress)
{
    if (tree == NULL)
        return false;

    memcpy(memoryAddress, tree->data, tree->typeSizeOf);

    return true;
}

void BinarySearchTreePrintTree(BinarySearchTree *root, int tabSize, char *pattern)
{
    for (int i = 0; i < tabSize; i++)
    {
        printf("-");
    }

    if (root != NULL)
    {
        printf("%d - ", root->key);
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

        BinarySearchTreePrintTree(root->left, tabSize + 2, pattern);
        printf("\n");
        BinarySearchTreePrintTree(root->right, tabSize + 2, pattern);
    }
    else
    {
        printf("NULL");
    }
}

BinarySearchTree *BinarySearchTreeRemoveKey(BinarySearchTree *tree, int key)
{
    BinarySearchTree *parentOfNodeToBeRemoved = NULL;
    BinarySearchTree *nodeToBeRemoved = BinarySearchTreeFindKey(tree, key, &parentOfNodeToBeRemoved);

    if (nodeToBeRemoved == NULL)
    {
        return NULL;
    }

    // 1* caso - se o nó é folha
    if (nodeToBeRemoved->left == NULL && nodeToBeRemoved->right == NULL)
    {
        if (parentOfNodeToBeRemoved->left != NULL && parentOfNodeToBeRemoved->left->key == key)
        {
            parentOfNodeToBeRemoved->left = NULL;
        }
        else if (parentOfNodeToBeRemoved->right != NULL && parentOfNodeToBeRemoved->right->key == key)
        {
            parentOfNodeToBeRemoved->right = NULL;
        }

        free(nodeToBeRemoved->data);
        free(nodeToBeRemoved);
        return tree;
    }

    // 2* caso = se o nó possui apenas uma subárvore
    if (nodeToBeRemoved->left == NULL && nodeToBeRemoved->right != NULL)
    {
        BinarySearchTree *temp = nodeToBeRemoved->right;

        nodeToBeRemoved->key = nodeToBeRemoved->right->key;
        free(nodeToBeRemoved->data);
        nodeToBeRemoved->data = nodeToBeRemoved->right->data;
        nodeToBeRemoved->typeSizeOf = nodeToBeRemoved->right->typeSizeOf;
        nodeToBeRemoved->left = nodeToBeRemoved->right->left;
        nodeToBeRemoved->right = nodeToBeRemoved->right->right;
        free(temp);
        return tree;
    }
    else if (nodeToBeRemoved->left != NULL && nodeToBeRemoved->right == NULL)
    {
        BinarySearchTree *temp = nodeToBeRemoved->left;

        nodeToBeRemoved->key = nodeToBeRemoved->left->key;
        free(nodeToBeRemoved->data);
        nodeToBeRemoved->data = nodeToBeRemoved->left->data;
        nodeToBeRemoved->typeSizeOf = nodeToBeRemoved->left->typeSizeOf;
        nodeToBeRemoved->left = nodeToBeRemoved->left->left;
        nodeToBeRemoved->right = nodeToBeRemoved->left->right;
        free(temp);
        return tree;
    }

    // 3* caso - se o nó possui duas sub árvores
    if (nodeToBeRemoved->left != NULL && nodeToBeRemoved->right != NULL)
    {
        BinarySearchTree *temp = nodeToBeRemoved;
        BinarySearchTree *tempParent = nodeToBeRemoved;

        temp = temp->left;
        while (temp->right != NULL)
        {
            tempParent = temp;
            temp = temp->right;
        }

        if (temp->key == nodeToBeRemoved->left->key)
        {
            nodeToBeRemoved->left = NULL;
        }

        nodeToBeRemoved->key = temp->key;
        free(nodeToBeRemoved->data);
        nodeToBeRemoved->data = temp->data;
        nodeToBeRemoved->typeSizeOf = temp->typeSizeOf;
        free(temp);
        tempParent->right = NULL;
        return tree;
    }

    return tree;
}