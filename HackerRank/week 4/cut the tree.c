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


long* subtree_sum;
long total_sum;
int* node_values;
int** adj;
int* adj_size;

long dfs(int u, int parent) {
    long sum = node_values[u];
    for (int i = 0; i < adj_size[u]; i++) {
        int v = adj[u][i];
        if (v != parent) {
            sum += dfs(v, u);
        }
    }
    subtree_sum[u] = sum;
    return sum;
}
/*
 * Complete the 'cutTheTree' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY data
 *  2. 2D_INTEGER_ARRAY edges
 */

int cutTheTree(int data_count, int* data, int edges_rows, int edges_columns, int** edges) {
    node_values = malloc(data_count * sizeof(int));
    subtree_sum = malloc(data_count * sizeof(long));
    adj = malloc(data_count * sizeof(int*));
    adj_size = calloc(data_count, sizeof(int));

    for (int i = 0; i < data_count; i++) {
        node_values[i] = data[i];
        adj[i] = NULL;
    }

    for (int i = 0; i < edges_rows; i++) {
        int u = edges[i][0] - 1;
        int v = edges[i][1] - 1;

        adj[u] = realloc(adj[u], (adj_size[u] + 1) * sizeof(int));
        adj[u][adj_size[u]++] = v;

        adj[v] = realloc(adj[v], (adj_size[v] + 1) * sizeof(int));
        adj[v][adj_size[v]++] = u;
    }

    total_sum = 0;
    for (int i = 0; i < data_count; i++) total_sum += node_values[i];

    dfs(0, -1);

    long min_diff = LONG_MAX;
    for (int i = 1; i < data_count; i++) {
        long diff = labs(total_sum - 2 * subtree_sum[i]);
        if (diff < min_diff) min_diff = diff;
    }

    for (int i = 0; i < data_count; i++) free(adj[i]);
    free(adj);
    free(adj_size);
    free(node_values);
    free(subtree_sum);

    return (int)min_diff;

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** data_temp = split_string(rtrim(readline()));

    int* data = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int data_item = parse_int(*(data_temp + i));

        *(data + i) = data_item;
    }

    int** edges = malloc((n - 1) * sizeof(int*));

    for (int i = 0; i < n - 1; i++) {
        *(edges + i) = malloc(2 * (sizeof(int)));

        char** edges_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int edges_item = parse_int(*(edges_item_temp + j));

            *(*(edges + i) + j) = edges_item;
        }
    }

    int result = cutTheTree(n, data, n - 1, 2, edges);

    fprintf(fptr, "%d\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
