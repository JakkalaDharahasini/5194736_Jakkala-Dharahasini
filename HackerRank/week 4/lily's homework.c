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

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

/* Pair struct to store value and original index */
typedef struct {
    int value;
    int index;
} Pair;

/* Compare function for qsort (ascending) */
int comparePairs(const void* a, const void* b) {
    Pair* p1 = (Pair*)a;
    Pair* p2 = (Pair*)b;
    return p1->value - p2->value;
}

/* Count minimal swaps to sort arr into ascending order */
int countSwaps(int n, int* arr) {
    Pair* arrPos = malloc(n * sizeof(Pair));
    int* visited = calloc(n, sizeof(int));
    int ans = 0;

    for (int i = 0; i < n; i++) {
        arrPos[i].value = arr[i];
        arrPos[i].index = i;
    }

    qsort(arrPos, n, sizeof(Pair), comparePairs);

    for (int i = 0; i < n; i++) {
        if (visited[i] || arrPos[i].index == i)
            continue;

        int cycle_size = 0;
        int j = i;

        while (!visited[j]) {
            visited[j] = 1;
            j = arrPos[j].index;
            cycle_size++;
        }

        if (cycle_size > 0)
            ans += (cycle_size - 1);
    }

    free(arrPos);
    free(visited);
    return ans;
}

/* Main function to compute Lily's Homework minimal swaps */
int lilysHomework(int n, int* arr) {
    int* arrCopy = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];
    int ascSwaps = countSwaps(n, arrCopy);

    // Descending
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];
    for (int i = 0; i < n; i++) arrCopy[i] = -arrCopy[i]; // invert to sort descending
    int descSwaps = countSwaps(n, arrCopy);
    free(arrCopy);

    return (ascSwaps < descSwaps) ? ascSwaps : descSwaps;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));
        *(arr + i) = arr_item;
    }

    int result = lilysHomework(n, arr);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

/* Helper functions for I/O */
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

    if (data[data_length - 1] == '\n') data[data_length - 1] = '\0';
    data = realloc(data, data_length + 1);
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
