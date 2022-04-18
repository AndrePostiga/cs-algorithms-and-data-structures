#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "Stack.h"

#define true 1
#define false 0

Stack *StackInit(int sizeOfType)
{
    Stack *newStack = malloc(sizeof(Stack));
    newStack->width = sizeOfType;
    newStack->nElems = 0;
    newStack->top = NULL;
    return newStack;
}

void StackPush(Stack *stack, const void *data)
{
    Node *newTopNode = (Node *)malloc(sizeof(Node));
    newTopNode->data = malloc(stack->width);
    memcpy(newTopNode->data, data, stack->width);

    newTopNode->next = stack->top;
    stack->top = newTopNode;
    stack->nElems++;
}

int StackPop(Stack *stack, void *memoryAddress)
{
    if (StackIsEmpty(stack))
        return false;

    Node *oldTopNode = stack->top;
    memcpy(memoryAddress, oldTopNode->data, stack->width);
    stack->top = oldTopNode->next;

    free(oldTopNode->data);
    free(oldTopNode);
    stack->nElems--;
    return true;
}

int StackIsEmpty(Stack *stack)
{
    return stack->nElems == 0;
}

void StackFree(Stack *stack)
{
    while (StackIsEmpty(stack) == false)
    {
        Node *oldTopNode = stack->top;
        stack->top = oldTopNode->next;

        free(oldTopNode->data);
        free(oldTopNode);
        stack->nElems--;
    }
    free(stack);
}

void StackPrint(Stack *stack)
{
    Node *currentNode = stack->top;
    while (currentNode != NULL)
    {
        printf("%d ", *(int *)currentNode->data);
        currentNode = currentNode->next;
    }
    printf("\n");
}