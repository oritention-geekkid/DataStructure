#include <stdio.h>
#include <stdlib.h>

/* 队列复用代码（使用数组） */
#define MAXSIZE 100
#define ElementType char
struct QNode {
    ElementType data[MAXsize];
    int front,rear;
    int size;
};
typedef struct QNode *Queue;

Queue createQueue(int size) {
    if(size<=MAXsize && size>0) {
        Queue pQ;
        pQ = (Queue)malloc(sizeof(struct QNode));
        pQ->front = 0;
        pQ->rear = 0;
        pQ->size = size;

        return pQ;
    }
    else {
        puts("Error! Invalid size input when creating a new queue.");
        return NULL;
    }
}
int isFull(Queue Q) {
    return (Q->front == (Q->rear+1)%Q->size);
}
int isEmpty(Queue Q) {
    return (Q->front == Q->rear);
}
void Enqueue(Queue Q, ElementType X) {
    if(!isFull(Q)) {
        Q->rear = (Q->rear+1)%Q->size;
        Q->data[Q->rear] = X;
    }
    else{puts("Error! Queue is full.");}
}
ElementType Dequeue(Queue Q) {
    if(!isEmpty(Q)) {
        Q->front = (Q->front+1)%Q->size;
        return Q->data[Q->front];
    }
    else{puts("Error! Queue is empty."); return 0;}
}
/* 队列复用代码（使用数组） */