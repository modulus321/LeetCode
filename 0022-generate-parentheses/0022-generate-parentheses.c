#include <stdlib.h>
#include <string.h>

void generate(char** result, char* current, int pos,
              int open, int close, int n, int* count) {

    if (pos == 2 * n) {
        current[pos] = '\0';
        result[*count] = malloc((2 * n + 1) * sizeof(char));
        strcpy(result[*count], current);
        (*count)++;
        return;
    }

    if (open < n) {
        current[pos] = '(';
        generate(result, current, pos + 1, open + 1, close, n, count);
    }

    if (close < open) {
        current[pos] = ')';
        generate(result, current, pos + 1, open, close + 1, n, count);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    int maxResults = 1430;
    char** result = malloc(maxResults * sizeof(char*));
    char* current = malloc((2 * n + 1) * sizeof(char));

    *returnSize = 0;

    generate(result, current, 0, 0, 0, n, returnSize);

    free(current);

    return result;
}
