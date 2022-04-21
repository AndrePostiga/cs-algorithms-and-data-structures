#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

typedef struct binarySearchTree
{
    int typeSizeOf;
    void *data;
    int key;
    struct binarySearchTree *left, *right;

} BinarySearchTree;

#endif /* BINARYSEARCHTREE_H */

// Todas as operações devem preservar a ordem entre os nós
// Não pode ser possível adicionar a mesma chave mais de uma vez em uma árvore binária

BinarySearchTree *BinarySearchTreeInit(int key, void *data, int typeSizeOfData);
BinarySearchTree *BinarySearchInsertNode(BinarySearchTree *tree, int key, void *data, int typeSizeOfData);
BinarySearchTree *BinarySearchInsertNode_rec(BinarySearchTree *tree, int key, void *data, int typeSizeOfData);
BinarySearchTree *BinarySearchTreeFindKey(BinarySearchTree *tree, int key, BinarySearchTree **parent);
BinarySearchTree *BinarySearchTreeFindKey_rec(BinarySearchTree *tree, int key, BinarySearchTree **parent);
BinarySearchTree *BinarySearchTreeRemoveKey(BinarySearchTree *tree, int key);
BinarySearchTree *BinarySearchTreeRemoveKey_rec(BinarySearchTree *tree, int key);
int BinarySearchTreeGetData(BinarySearchTree *tree, void *memoryAddress);
void BinarySearchTreePrintTree(BinarySearchTree *root, int tabSize, char *pattern);
void PrintTreeGraphicaly(BinarySearchTree *t);