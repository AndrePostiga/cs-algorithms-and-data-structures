#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "BinarySearchTree.h"

#define true 1
#define false 0

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

        if (parent != NULL)
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
    BinarySearchTree *nodeToBeRemoved = tree;

    while (nodeToBeRemoved != NULL)
    {
        if (key == nodeToBeRemoved->key)
            break;

        parentOfNodeToBeRemoved = nodeToBeRemoved;

        if (key < nodeToBeRemoved->key)
            nodeToBeRemoved = nodeToBeRemoved->left;
        else if (key > nodeToBeRemoved->key)
            nodeToBeRemoved = nodeToBeRemoved->right;
    }

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

        nodeToBeRemoved->key = temp->key;
        free(nodeToBeRemoved->data);
        nodeToBeRemoved->data = temp->data;
        nodeToBeRemoved->typeSizeOf = temp->typeSizeOf;
        nodeToBeRemoved->left = temp->left;
        nodeToBeRemoved->right = temp->right;
        free(temp);
        return tree;
    }
    else if (nodeToBeRemoved->left != NULL && nodeToBeRemoved->right == NULL)
    {
        BinarySearchTree *temp = nodeToBeRemoved->left;

        nodeToBeRemoved->key = temp->key;
        free(nodeToBeRemoved->data);
        nodeToBeRemoved->data = temp->data;
        nodeToBeRemoved->typeSizeOf = temp->typeSizeOf;
        nodeToBeRemoved->right = temp->right;
        nodeToBeRemoved->left = temp->left;
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

        // se tentar remover a raiz
        if (tempParent == nodeToBeRemoved)
            tempParent = NULL;

        // caso a esquerda seja trocada pelo que será removido
        if (temp->key == nodeToBeRemoved->left->key)
            nodeToBeRemoved->left = NULL;

        nodeToBeRemoved->key = temp->key;
        free(nodeToBeRemoved->data);
        nodeToBeRemoved->data = temp->data;
        nodeToBeRemoved->typeSizeOf = temp->typeSizeOf;

        // caso o nó que será substituido possuir elemento a esquerda, devemos reapontar a esquerda dele
        if (tempParent != NULL)
        {
            tempParent->right = temp->left;
        }

        free(temp);
        return tree;
    }

    return tree;
}

BinarySearchTree *BinarySearchTreeRemoveKey_rec(BinarySearchTree *tree, int key)
{
    if (tree == NULL)
        return NULL;

    if (tree->key == key)
    {
        if (tree->left == NULL && tree->right == NULL) // primeiro caso - folha
        {
            free(tree->data);
            free(tree);
            return NULL;
        }

        // segundo caso - subarvore esquerda ou direita
        if (tree->left == NULL && tree->right != NULL) // direita
        {
            BinarySearchTree *temp = tree->right;
            free(tree->data);
            free(tree);
            return temp;
        }
        else if (tree->left != NULL && tree->right == NULL) // esquerda
        {
            BinarySearchTree *temp = tree->left;
            free(tree->data);
            free(tree);
            return temp;
        }

        // terceiro caso - subarvore esquerda e direita
        if (tree->left != NULL && tree->right != NULL) // primeiro caso - folha
        {
            // colocar alguém no lugar da raiz
            // retornar esse alguem com tudo que a raiz apontava antes
            BinarySearchTree *newRoot = tree->left;
            while (newRoot->right != NULL)
                newRoot = newRoot->right;

            tree->typeSizeOf = newRoot->typeSizeOf;
            memcpy(tree->data, newRoot->data, newRoot->typeSizeOf);
            tree->key = newRoot->key;

            tree->left = BinarySearchTreeRemoveKey_rec(tree->left, newRoot->key);
            return tree;
        }
    }
    else
    {
        if (key < tree->key)
            tree->left = BinarySearchTreeRemoveKey_rec(tree->left, key);
        else if (key > tree->key)
            tree->right = BinarySearchTreeRemoveKey_rec(tree->right, key);

        return tree;
    }

    return tree;
}

// Código gigantesco para imprimir uma árvore binária de forma gráfica
#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
int print_next;
#define INFINITY (1 << 20)
// adjust gap between left and right nodes
int gap = 1;

int MIN(int X, int Y)
{
    return ((X) < (Y)) ? (X) : (Y);
}
int MAX(int X, int Y)
{
    return ((X) > (Y)) ? (X) : (Y);
}
typedef struct asciinode_struct
{
    struct asciinode_struct *left, *right;

    // length of the edge from this node to its children
    int edge_length;

    int height;

    int lablen;

    //-1=I am left, 0=I am root, 1=right
    int parent_dir;

    // max supported unit32 in dec, 10 digits max
    char label[11];
} asciinode;
void print_level(asciinode *node, int x, int level)
{
    // This function prints the given level of the given tree, assuming
    // that the node has the given x cordinate.

    int i, isleft;
    if (node == NULL)
        return;
    isleft = (node->parent_dir == -1);
    if (level == 0)
    {
        for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++)
        {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->lablen;
    }
    else if (node->edge_length >= level)
    {
        if (node->left != NULL)
        {
            for (i = 0; i < (x - print_next - (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->right != NULL)
        {
            for (i = 0; i < (x - print_next + (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else
    {
        print_level(node->left,
                    x - node->edge_length - 1,
                    level - node->edge_length - 1);
        print_level(node->right,
                    x + node->edge_length + 1,
                    level - node->edge_length - 1);
    }
}
asciinode *build_ascii_tree_recursive(BinarySearchTree *t)
{
    asciinode *node;

    if (t == NULL)
        return NULL;

    node = malloc(sizeof(asciinode));
    node->left = build_ascii_tree_recursive(t->left);
    node->right = build_ascii_tree_recursive(t->right);

    if (node->left != NULL)
    {
        node->left->parent_dir = -1;
    }

    if (node->right != NULL)
    {
        node->right->parent_dir = 1;
    }

    sprintf(node->label, "%d", t->key);
    node->lablen = strlen(node->label);

    return node;
}
asciinode *build_ascii_tree(BinarySearchTree *t)
{
    // Copy the tree into the ascii node structre
    asciinode *node;
    if (t == NULL)
        return NULL;
    node = build_ascii_tree_recursive(t);
    node->parent_dir = 0;
    return node;
}
void free_ascii_tree(asciinode *node)
{
    // Free all the nodes of the given tree
    if (node == NULL)
        return;
    free_ascii_tree(node->left);
    free_ascii_tree(node->right);
    free(node);
}
void compute_lprofile(asciinode *node, int x, int y)
{
    // The following function fills in the lprofile array for the given tree.
    // It assumes that the center of the label of the root of this tree
    // is located at a position (x,y).  It assumes that the edge_length
    // fields have been computed for this tree.
    int i, isleft;
    if (node == NULL)
        return;
    isleft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
    if (node->left != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}
void compute_rprofile(asciinode *node, int x, int y)
{
    int i, notleft;
    if (node == NULL)
        return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
    if (node->right != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}
void compute_edge_lengths(asciinode *node)
{
    // This function fills in the edge_length and
    // height fields of the specified tree
    int h, hmin, i, delta;
    if (node == NULL)
        return;
    compute_edge_lengths(node->left);
    compute_edge_lengths(node->right);

    /* first fill in the edge_length of node */
    if (node->right == NULL && node->left == NULL)
    {
        node->edge_length = 0;
    }
    else
    {
        if (node->left != NULL)
        {
            for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
            {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->left, 0, 0);
            hmin = node->left->height;
        }
        else
        {
            hmin = 0;
        }
        if (node->right != NULL)
        {
            for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++)
            {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->right, 0, 0);
            hmin = MIN(node->right->height, hmin);
        }
        else
        {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++)
        {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        // If the node has two children of height 1, then we allow the
        // two leaves to be within 1, instead of 2
        if (((node->left != NULL && node->left->height == 1) ||
             (node->right != NULL && node->right->height == 1)) &&
            delta > 4)
        {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    // now fill in the height of node
    h = 1;
    if (node->left != NULL)
    {
        h = MAX(node->left->height + node->edge_length + 1, h);
    }
    if (node->right != NULL)
    {
        h = MAX(node->right->height + node->edge_length + 1, h);
    }
    node->height = h;
}
void PrintTreeGraphicaly(BinarySearchTree *t)
{
    asciinode *proot;
    int xmin, i;
    if (t == NULL)
        return;
    proot = build_ascii_tree(t);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++)
    {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT)
    {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
}