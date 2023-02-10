#include <stdio.h>
#include <stdlib.h>

/* 并查集复用代码（使用数组） */
struct SNode {
    int *data;
    int maxSize;
};
typedef struct SNode *UFSet;

UFSet createUnionFindSet(int maxSize) {
    UFSet S = (UFSet)malloc(sizeof(struct SNode));
    S->data = (int *)malloc(maxSize*sizeof(int));
    for (int i=0; i<maxSize; i++) {
        S->data[i] = -1;
    }
    S->maxSize = maxSize;

    return S;
}
int findRoot(UFSet S, int X) {
    if (S->data[X]<0) {
        return X;
    }
    else {
        return S->data[X] = findRoot(S,S->data[X]);
    }
}
void Union(UFSet S, int e1, int e2) {
    int root1 = findRoot(S,e1);
    int root2 = findRoot(S,e2);
    if (S->data[root1]<S->data[root2]) {
        S->data[root2] = root1;
    }
    else {
        if(S->data[root1]==S->data[root2]) {
            S->data[root2]--;
        }
        S->data[root1] = root2;
    }
}
/* 并查集复用代码（使用数组） */