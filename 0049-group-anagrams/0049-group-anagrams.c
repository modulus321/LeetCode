#include <stdlib.h>
#include <string.h>

char*** groupAnagrams(char** strs, int strsSize, int* returnSize,
                      int** returnColumnSizes) {

    char*** result = malloc(strsSize * sizeof(char**));
    *returnColumnSizes = malloc(strsSize * sizeof(int));
    *returnSize = 0;

    int (*count)[26] = calloc(strsSize, sizeof(int[26]));

    for (int i = 0; i < strsSize; i++) {

        int freq[26] = {0};

        for (int j = 0; strs[i][j] != '\0'; j++) {
            freq[strs[i][j] - 'a']++;
        }

        int found = -1;

        for (int j = 0; j < *returnSize; j++) {

            int same = 1;

            for (int k = 0; k < 26; k++) {
                if (count[j][k] != freq[k]) {
                    same = 0;
                    break;
                }
            }

            if (same) {
                found = j;
                break;
            }
        }

        if (found == -1) {

            found = *returnSize;

            for (int k = 0; k < 26; k++) {
                count[found][k] = freq[k];
            }

            result[found] = malloc(strsSize * sizeof(char*));
            (*returnColumnSizes)[found] = 0;

            (*returnSize)++;
        }

        int pos = (*returnColumnSizes)[found];

        result[found][pos] = malloc(strlen(strs[i]) + 1);
        strcpy(result[found][pos], strs[i]);

        (*returnColumnSizes)[found]++;
    }

    free(count);

    return result;
}