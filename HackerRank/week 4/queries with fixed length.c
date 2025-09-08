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

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER_ARRAY queries
 */
int* solve(int arr_count, int* arr, int queries_count, int* queries, int* result_count) {
    int n = arr_count;
    if (n <= 0) {
        *result_count = queries_count;
        int *res_empty = malloc(queries_count * sizeof(int));
        for (int i = 0; i < queries_count; i++) res_empty[i] = 0;
        return res_empty;
    }

    // allocate helper arrays
    int *left = malloc(n * sizeof(int));
    int *right = malloc(n * sizeof(int));
    int *stack = malloc(n * sizeof(int));
    int top = -1;

    // previous greater (strict): for each i, left[i] = index of previous element > arr[i], or -1
    top = -1;
    for (int i = 0; i < n; i++) {
        while (top >= 0 && arr[stack[top]] <= arr[i]) top--;
        left[i] = (top == -1) ? -1 : stack[top];
        stack[++top] = i;
    }

    // next greater or equal: for each i, right[i] = index of next element >= arr[i], or n
    top = -1;
    for (int i = n - 1; i >= 0; i--) {
        while (top >= 0 && arr[stack[top]] < arr[i]) top--;
        right[i] = (top == -1) ? n : stack[top];
        stack[++top] = i;
    }

    free(stack);

    // ans[len] = minimal value that can be the maximum of some subarray of length exactly len
    int *ans = malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) ans[i] = INT_MAX;

    for (int i = 0; i < n; i++) {
        int span = right[i] - left[i] - 1; // maximum length where arr[i] can be maximum
        if (arr[i] < ans[span]) ans[span] = arr[i];
    }

    // propagate minima: if an element can be max for span S, it can also be max for any length <= S
    for (int len = n - 1; len >= 1; len--) {
        if (ans[len + 1] < ans[len]) ans[len] = ans[len + 1];
    }

    // prepare result for queries
    int *res = malloc(queries_count * sizeof(int));
    for (int i = 0; i < queries_count; i++) {
        int d = queries[i];
        if (d >= 1 && d <= n) {
            res[i] = ans[d];
        } else {
            // no subarray of length d exists; depending on problem constraints,
            // set to 0 or INT_MAX. Here we set to 0 as a safe placeholder.
            res[i] = 0;
        }
    }

    free(left);
    free(right);
    free(ans);

    *result_count = queries_count;
    return res;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));
    int q = parse_int(*(first_multiple_input + 1));

    char** arr_temp = split_string(rtrim(readline()));
    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));
        arr[i] = arr_item;
    }

    int* queries = malloc(q * sizeof(int));
    for (int i = 0; i < q; i++) {
        int queries_item = parse_int(ltrim(rtrim(readline())));
        queries[i] = queries_item;
    }

    int result_count;
    int* result = solve(n, arr, q, queries, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d", result[i]);
        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }
    fprintf(fptr, "\n");

    fclose(fptr);

    free(arr);
    free(queries);
    free(result);

    return 0;
}

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

    data = realloc(data, data_length + 1);
    return data;
}

char* ltrim(char* str) {
    if (!str) return NULL;
    if (!*str) return str;
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return NULL;
    if (!*str) return str;
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
        if (!splits) return splits;
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
