#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
typedef struct {
    int *arr;
    int top;
    int capacity;
} Stack;
Stack* createStack(int capacity){
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->arr = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}
int isEmpty(Stack *stack) {
    return stack->top == -1;
}
void push(Stack *stack, int value){
    stack->arr[++stack->top] = value;
}
int pop(Stack *stack) {
    return stack->arr[stack->top--];
}int peek(Stack *stack){
    return stack->arr[stack->top];
}
Stack *s1, *s2;
void enqueue(int value) {
    push(s1, value);
}
void dequeue(){
    if (isEmpty(s2)) {
        while (!isEmpty(s1)) {
            push(s2, pop(s1));
        }
    }
    if (!isEmpty(s2)) {
        pop(s2);
    }
}
int front(){
    if (isEmpty(s2)) {
        while (!isEmpty(s1)) {
            push(s2, pop(s1));
        }
    }
    return peek(s2);
}
int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int q;
    scanf("%d", &q);
    s1 = createStack(q);
    s2 = createStack(q);
    while (q--) {
        int type, x;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d", &x);
            enqueue(x);
        } else if (type == 2){
            dequeue();
        } else if (type == 3){
            printf("%d\n", front());
        }   
    }    
    return 0;
}
