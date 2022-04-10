#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef struct tree
{
    int typeSizeOf;
    void *data;
    struct tree *left, *right;

} Tree;

#endif /* BINARYTREE_H */

Tree *BinaryTreeInit(void *data, int typeSizeOfData);
int BinaryTreeGetData(Tree *tree, void *memoryAddress);
void BinaryTreePrintTree(Tree *root, int tabSize, char *pattern);

// int BinaryTreeCountNodes(Node *root);
// int BinaryTreeCountLeafes(Node *root);
// void BinaryTreeDepthFirstTraversal(Node *root);
// void BinaryTreeBeadthFirstTraversal(Node *root);
// void BinaryTreePreOrderTraversal(Node *root);
// void BinaryTreePostOrderTraversal(Node *root);
// void BinaryTreeInOrderTraversal(Node *root);
// int BinaryTreeHeight(Node *root);