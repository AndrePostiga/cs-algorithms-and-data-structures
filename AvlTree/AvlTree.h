#ifndef AVLTREE_H
#define AVLTREE_H

typedef struct avlTree
{
    int typeSizeOf;
    void *data;

    int key;
    short balanceFactor;
    struct avlTree *left, *right;

} AvlTree;

#endif /* AVLTREE_H */

// Todas as operações devem preservar a ordem entre os nós e seu balanceamento
// Não pode ser possível adicionar a mesma chave mais de uma vez em uma árvore binária

AvlTree *AvlTreeInit(int key, void *data, int typeSizeOfData);
AvlTree *AvlTreeInsertNode(AvlTree *tree, int key, void *data, int typeSizeOfData);
AvlTree *AvlTreeInsertNode_rec(AvlTree *tree, int key, void *data, int typeSizeOfData);
// AvlTree *AvlTreeFindKey(AvlTree *tree, int key, AvlTree **parent);
// AvlTree *AvlTreeFindKey_rec(AvlTree *tree, int key, AvlTree **parent);
// AvlTree *AvlTreeRemoveKey(AvlTree *tree, int key);
// AvlTree *AvlTreeRemoveKey_rec(AvlTree *tree, int key);
// int AvlTreeGetData(AvlTree *tree, void *memoryAddress);
// void AvlTreePrintTree(AvlTree *root, int tabSize, char *pattern);
void PrintTreeGraphicaly(AvlTree *t);

AvlTree *RotateLeft(AvlTree *root);
AvlTree *RotateRight(AvlTree *root);