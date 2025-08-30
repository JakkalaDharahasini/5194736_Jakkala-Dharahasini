#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helpers already given
char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);

// Min-Heap implementation
void heapify_down(int* heap, int size, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && heap[left] < heap[smallest])
        smallest = left;
    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != idx) {
        int temp = heap[idx];
        heap[idx] = heap[smallest];
        heap[smallest] = temp;
        heapify_down(heap, size, smallest);
    }
}

void heapify_up(int* heap, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap[parent] > heap[idx]) {
            int temp = heap[parent];
            heap[parent] = heap[idx];
            heap[idx] = temp;
            idx = parent;
        } else break;
    }
}

int extract_min(int* heap, int* size) {
    if (*size <= 0) return INT_MAX;
    int root = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify_down(heap, *size, 0);
    return root;
}

void insert_heap(int* heap, int* size, int val) {
    heap[*size] = val;
    (*size)++;
    heapify_up(heap, *size - 1);
}

// The cookies function
int cookies(int k, int A_count, int* A) {
    // Build heap
    int heap[A_count * 2]; 
    int size = 0;
    for (int i = 0; i < A_count; i++) {
        insert_heap(heap, &size, A[i]);
    }

    int operations = 0;
    while (size > 1 && heap[0] < k) {
        int least = extract_min(heap, &size);
        int second = extract_min(heap, &size);

        long long new_cookie = (long long)least + 2LL * second;
        insert_heap(heap, &size, (int)new_cookie);
        operations++;
    }

    if (size > 0 && heap[0] >= k) return operations;
    return -1;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));
    int k = parse_int(*(first_multiple_input + 1));

    char** A_temp = split_string(rtrim(readline()));

    int* A = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int A_item = parse_int(*(A_temp + i));
        *(A + i) = A_item;
    }

    int result = cookies(k, n, A);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

// Helper functions (given)
char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) break;

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;

        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) return NULL;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) return NULL;
    while (*str && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return NULL;
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}