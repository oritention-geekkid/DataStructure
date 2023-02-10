#include <stdio.h>
#include <stdlib.h>

/* 最小堆复用代码（使用数组） */
#define ElementType int
struct HNode {
    ElementType *data;
    int currentSize;
    int capacity;
};
typedef struct HNode *MinHeap;

#define MINDATA -1  // 哨兵元素定义

MinHeap createMinHeap(int capacity) {
    MinHeap minH = (MinHeap)malloc(sizeof(struct HNode));
    minH->data = (ElementType *)malloc((capacity+1)*sizeof(ElementType));
    minH->currentSize = 0;
    minH->capacity = capacity;
    minH->data[0] = MINDATA;

    return minH;
}
int isEmpty(MinHeap H) {
    return (H->currentSize==0);
}
int isFull(MinHeap H) {
    return (H->currentSize==H->capacity);
}
void percolateDown (MinHeap H, int root) {
    int currentLocation = root;
    int minChild;
    ElementType rootValue = H->data[root];

    for (;currentLocation*2<=H->currentSize;currentLocation=minChild) {
        minChild = currentLocation*2;
        if (minChild!=H->currentSize&&H->data[minChild]>H->data[minChild+1]) {
            minChild++;
        }
        if (rootValue<=H->data[minChild]) {
            break;
        }
        else {
            H->data[currentLocation] = H->data[minChild];
        }
    }

    H->data[currentLocation] = rootValue;
}
void insert(MinHeap H, ElementType X) {
    if (isFull(H)) puts("Error! Heap is full.");
    else {
        int insertLocator = ++H->currentSize;
        for (;H->data[insertLocator/2]>X;insertLocator/2) {
            H->data[insertLocator] = H->data[insertLocator/2];
        }
        H->data[insertLocator] = X;
    }
}
ElementType popTop(MinHeap H) {
    if (isEmpty(H)) {
        puts("Error! Heap is full.");
        return -1;
    } 
    else {
        ElementType topValue = H->data[1];
        H->data[1] = H->data[H->currentSize--];
        percolateDown(H,1);
        return topValue;
    }

}
MinHeap buildMinHeap(ElementType *elements, int capacity) {
    MinHeap ret = createMinHeap(capacity);
    ret->currentSize = capacity;
    for (int i=1;i<=capacity;i++) {
        ret->data[i] = elements[i-1];
    }
    for (int i=ret->currentSize;i>0;i--) {
        percolateDown(ret,i);
    }

    return ret;
}
/* 最小堆复用代码（使用数组） */