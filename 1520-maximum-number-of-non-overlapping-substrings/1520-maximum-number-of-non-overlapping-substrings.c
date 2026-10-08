
#include <stdlib.h>
#include <string.h>

char** maxNumOfSubstrings(char* s, int* returnSize) {
    int n = strlen(s);
    int first[26], last[26];

    for (int i = 0; i < 26; i++) {
        first[i] = n;
        last[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (first[c] == n)
            first[c] = i;
        last[c] = i;
    }

    int start[26], end[26], count = 0;

    for (int i = 0; i < 26; i++) {
        if (last[i] == -1)
            continue;

        int l = first[i];
        int r = last[i];
        int valid = 1;

        for (int j = l; j <= r; j++) {
            int c = s[j] - 'a';

            if (first[c] < l) {
                valid = 0;
                break;
            }

            if (last[c] > r)
                r = last[c];
        }

        if (valid) {
            start[count] = l;
            end[count] = r;
            count++;
        }
    }

    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (end[i] > end[j]) {
                int temp = end[i];
                end[i] = end[j];
                end[j] = temp;

                temp = start[i];
                start[i] = start[j];
                start[j] = temp;
            }
        }
    }

    char** result = malloc(26 * sizeof(char*));
    *returnSize = 0;
    int prevEnd = -1;

    for (int i = 0; i < count; i++) {
        if (start[i] > prevEnd) {
            int len = end[i] - start[i] + 1;

            result[*returnSize] = malloc(len + 1);
            strncpy(result[*returnSize], s + start[i], len);
            result[*returnSize][len] = '\0';

            (*returnSize)++;
            prevEnd = end[i];
        }
    }

    return result;
}
