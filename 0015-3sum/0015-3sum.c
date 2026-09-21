#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int capacity = 1000;
    int **result = malloc(capacity * sizeof(int *));
    *returnSize = 0;

    qsort(nums, numsSize, sizeof(int), compare);

    for (int i = 0; i < numsSize - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {
            long sum = (long)nums[i] + nums[left] + nums[right];

            if (sum == 0) {
                if (*returnSize >= capacity) {
                    capacity *= 2;
                    result = realloc(result, capacity * sizeof(int *));
                }

                result[*returnSize] = malloc(3 * sizeof(int));

                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[left];
                result[*returnSize][2] = nums[right];

                (*returnSize)++;

                left++;
                right--;

                while (left < right && nums[left] == nums[left - 1])
                    left++;

                while (left < right && nums[right] == nums[right + 1])
                    right--;

            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }

    *returnColumnSizes = malloc(*returnSize * sizeof(int));

    for (int i = 0; i < *returnSize; i++)
        (*returnColumnSizes)[i] = 3;

    return result;
}