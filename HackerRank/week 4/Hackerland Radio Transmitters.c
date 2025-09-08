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

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/*
 * Complete the 'hackerlandRadioTransmitters' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY x
 *  2. INTEGER k
 */
int hackerlandRadioTransmitters(int x_count, int* x, int k) {
    qsort(x, x_count, sizeof(int), compare);

    int i = 0, count = 0;
    while (i < x_count) {
        count++;

        // Move to the farthest house within k units from the starting house
        int loc = x[i] + k;
        while (i < x_count && x[i] <= loc) i++;

        // Place transmitter at the farthest house within range
        int transmitter = x[i - 1];

        // Skip all houses covered by this transmitter
        loc = transmitter + k;
        while (i < x_count && x[i] <= loc) i++;
    }
    return count;
}

int main() {
    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));
    int k = parse_int(*(first_multiple_input + 1));

    char** x_temp = split_string(rtrim(readline()));

    int* x = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int x_item = parse_int(*(x_temp + i));
        *(x + i) = x_item;
    }

    int result = hackerlandRadioTransmitters(n, x, k);
    printf("%d\n", result);

    free(x);
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
        splits = realloc(splits, sizeof(char*) * (++spaces));
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
