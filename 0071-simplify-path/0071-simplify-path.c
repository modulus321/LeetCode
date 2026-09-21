#include <stdlib.h>
#include <string.h>

char* simplifyPath(char* path) {

    char** stack = malloc(3001 * sizeof(char*));
    int top = 0;

    char* token = strtok(path, "/");

    while (token != NULL) {

        if (strcmp(token, ".") == 0) {
            // Do nothing
        }
        else if (strcmp(token, "..") == 0) {
            if (top > 0)
                top--;
        }
        else {
            stack[top++] = token;
        }

        token = strtok(NULL, "/");
    }

    char* result = malloc(3001 * sizeof(char));
    int pos = 0;

    result[pos++] = '/';

    for (int i = 0; i < top; i++) {

        int len = strlen(stack[i]);

        memcpy(result + pos, stack[i], len);
        pos += len;

        if (i < top - 1)
            result[pos++] = '/';
    }

    result[pos] = '\0';

    free(stack);

    return result;
}