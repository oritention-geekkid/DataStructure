#include <stdio.h>
#include <stdlib.h>

/* 栈复用代码（使用数组） */
#define MAXSIZE 100
#define ElementType int
struct StackNode {
    ElementType data[MAXSIZE];
    int top;
};
typedef struct StackNode *Stack;

Stack createStack() {
    Stack S = (Stack)malloc(sizeof(struct StackNode));
    S->top = -1;

    return S;
}
int isEmpty(Stack S) {
    if (S->top < 0) {
        return 1;
    }
    else {
        return 0;
    }

}
int isFull(Stack S) {
    if (S->top == MAXSIZE-1) {
        return 1;
    }
    else {
        return 0;
    }
}
void push(Stack S, ElementType X) {
    if(isFull(S)) puts("Error! Stack is full.");
    else S->data[++(S->top)] = X;
}
ElementType pop(Stack S) {
    if(isEmpty(S)) puts("Error! Stack is empty.");
    else return S->data[(S->top)--];
}
ElementType gettop(Stack S) {
    if(isEmpty(S)) puts("Error! Stack is empty.");
    else return S->data[(S->top)];
}
/* 栈复用代码（使用数组） */