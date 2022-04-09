#include "stdlib.h"
#include "stdio.h"
#include "Queue.h"

#define true 1
#define false 0

Queue *QueueInit(int sizeOfType)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    queue->width = sizeOfType;
    queue->head = NULL;
    queue->tail = NULL;
    queue->nElems = 0;
    return queue;
}

void Enqueue(Queue *queue, void *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = malloc(queue->width);
    newNode->next = NULL;
    memcpy(newNode->data, data, queue->width);

    if (QueueIsEmpty(queue))
    {
        queue->head = queue->tail = newNode;
    }
    else
    {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }

    queue->nElems++;
}

int Dequeue(Queue *queue, void *memoryAddress)
{
    if (QueueIsEmpty(queue))
        return false;

    Node *oldFirstNode = queue->head;
    memcpy(memoryAddress, oldFirstNode->data, queue->width);

    if (QueueIsEmpty(queue) == false)
    {
        queue->head = oldFirstNode->next;
    }
    else
    {
        queue->head = NULL;
        queue->tail = NULL;
    }

    free(oldFirstNode->data);
    free(oldFirstNode);
    queue->nElems--;
    return true;
}

int QueueIsEmpty(Queue *queue)
{
    return QueueSize(queue) == 0;
}

int QueueSize(Queue *queue)
{
    return queue->nElems;
}

void QueueFree(Queue *queue)
{
    Node *currentNode = queue->head;
    Node *nextNode;

    while (currentNode != NULL)
    {
        nextNode = currentNode->next;
        free(currentNode->data);
        free(currentNode);
        currentNode = nextNode;
    }

    free(queue);
}

void QueuePrint(Queue *queue)
{
    Node *current = queue->head;
    while (current != NULL)
    {
        printf("%d ", *(int *)current->data);
        current = current->next;
    }
    printf("\n");
}