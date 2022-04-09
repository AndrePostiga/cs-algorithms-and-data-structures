#ifndef STACK_H
#define STACK_H

typedef struct Node
{
    struct Node *next;
    void *data;
} Node;

typedef struct stack
{
    int width;  // width in bytes of the type of data stored in the stack
    int nElems; // number of elements
    Node *top;
} Stack;

Stack *StackInit(int sizeOfType);
void StackPush(Stack *stack, const void *data);
int StackPop(Stack *stack, void *memoryAddress);
int StackIsEmpty(Stack *stack);
void StackFree(Stack *stack);
void StackPrint(Stack *stack);

#endif /* STACK_H */