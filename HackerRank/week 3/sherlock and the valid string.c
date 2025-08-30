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

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char* isValid(char* s) {
    int freq[26] = {0};
    int len = strlen(s);
    for (int i = 0; i < len; i++){
        freq[s[i] - 'a']++;
    }
    int count[26], csize = 0;
    for (int i = 0; i < 26; i++){
        if (freq[i] > 0){
            count[csize++] = freq[i];
        }
    }
    int min = count[0], max = count[0];
    for (int i = 1; i < csize; i++){
        if (count[i] < min) min = count[i];
        if (count[i] > max) max = count[i];
    }
    if (min == max){
        char* ans = malloc(4);
        strcpy(ans, "YES");
        return ans;
    }
    int minCount = 0, maxCount = 0;
    for (int i = 0; i < csize; i++){
        if (count[i] == min) minCount++;
        else if (count[i] == max)  maxCount++;
    }
    if (min == 1 && minCount == 1 && (maxCount + minCount == csize)){
        char* ans = malloc(4);
        strcpy(ans, "YES");
        return ans;
    }
    if (max - min == 1 && maxCount == 1){
        char* ans = malloc(4);
        strcpy(ans, "YES");
        return ans;
    }
    char* ans = malloc(3);
    strcpy(ans, "NO");
    return ans;

}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = isValid(s);

    fprintf(fptr, "%s\n", result);

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
