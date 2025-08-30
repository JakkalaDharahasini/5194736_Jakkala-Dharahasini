#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int heap[MAX + 5];
int heapSize = 0;

// Swap helper
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up
void heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] > heap[i]) {
            swap(&heap[parent], &heap[i]);
            i = parent;
        } else break;
    }
}

// Heapify down
void heapifyDown(int i) {
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heapSize && heap[left] < heap[smallest]) smallest = left;
        if (right < heapSize && heap[right] < heap[smallest]) smallest = right;

        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else break;
    }
}

// Insert into heap
void insertHeap(int val) {
    heap[heapSize] = val;
    heapifyUp(heapSize);
    heapSize++;
}

// Delete element from heap
void deleteHeap(int val) {
    int i;
    for (i = 0; i < heapSize; i++) {
        if (heap[i] == val) break;
    }
    if (i == heapSize) return; // not found (shouldn't happen as per problem)

    heap[i] = heap[heapSize - 1];
    heapSize--;

    heapifyDown(i);
    heapifyUp(i);
}

// Get minimum
int getMin() {
    return heap[0];
}

int main() {
    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int type, val;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d", &val);
            insertHeap(val);
        } else if (type == 2) {
            scanf("%d", &val);
            deleteHeap(val);
        } else if (type == 3) {
            printf("%d\n", getMin());
        }
    }

    return 0;
}