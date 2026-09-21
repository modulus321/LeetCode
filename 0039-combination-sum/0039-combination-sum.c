#include <stdlib.h>

void backtrack(int* candidates, int candidatesSize, int target,
               int start, int* current, int currentSize,
               int** result, int* returnSize, int* returnColumnSizes) {

    if (target == 0) {
        result[*returnSize] = malloc(currentSize * sizeof(int));

        for (int i = 0; i < currentSize; i++)
            result[*returnSize][i] = current[i];

        returnColumnSizes[*returnSize] = currentSize;
        (*returnSize)++;
        return;
    }

    for (int i = start; i < candidatesSize; i++) {

        if (candidates[i] > target)
            continue;

        current[currentSize] = candidates[i];

        backtrack(candidates, candidatesSize,
                  target - candidates[i],
                  i, current, currentSize + 1,
                  result, returnSize, returnColumnSizes);
    }
}

int** combinationSum(int* candidates, int candidatesSize,
                     int target, int* returnSize,
                     int** returnColumnSizes) {

    int** result = malloc(150 * sizeof(int*));
    *returnColumnSizes = malloc(150 * sizeof(int));

    int* current = malloc(target * sizeof(int));

    *returnSize = 0;

    backtrack(candidates, candidatesSize, target,
              0, current, 0,
              result, returnSize, *returnColumnSizes);

    free(current);

    return result;
}