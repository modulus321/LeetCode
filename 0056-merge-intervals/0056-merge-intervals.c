#include <stdlib.h>

int compare(const void *a, const void *b) {
    int *x = *(int **)a;
    int *y = *(int **)b;

    return x[0] - y[0];
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize,
            int* returnSize, int** returnColumnSizes) {

    qsort(intervals, intervalsSize, sizeof(int *), compare);

    int** result = malloc(intervalsSize * sizeof(int *));
    *returnColumnSizes = malloc(intervalsSize * sizeof(int));

    *returnSize = 0;

    for (int i = 0; i < intervalsSize; i++) {

        if (*returnSize == 0 ||
            intervals[i][0] > result[*returnSize - 1][1]) {

            result[*returnSize] = malloc(2 * sizeof(int));

            result[*returnSize][0] = intervals[i][0];
            result[*returnSize][1] = intervals[i][1];

            (*returnColumnSizes)[*returnSize] = 2;
            (*returnSize)++;

        } else {

            if (intervals[i][1] > result[*returnSize - 1][1])
                result[*returnSize - 1][1] = intervals[i][1];
        }
    }

    return result;
}