#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node
{
    struct Node *next;
    void *data;
} Node;

typedef struct queue
{
    int width;  // width in bytes of the type of data stored in the stack
    int nElems; // number of elements
    Node *head;
    Node *tail;
} Queue;

#endif /* QUEUE_H */

Queue *QueueInit(int sizeOfType);
void Enqueue(Queue *queue, void *data);
int Dequeue(Queue *queue, void *memoryAddress);

int QueueIsEmpty(Queue *queue);
int QueueSize(Queue *queue);
void QueueFree(Queue *queue);
void QueuePrint(Queue *queue);