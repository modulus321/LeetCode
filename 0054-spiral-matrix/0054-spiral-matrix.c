int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {

    int rows = matrixSize;
    int cols = matrixColSize[0];

    int* result = malloc(rows * cols * sizeof(int));

    int top = 0;
    int bottom = rows - 1;
    int left = 0;
    int right = cols - 1;

    *returnSize = 0;

    while (top <= bottom && left <= right) {

        // Left to right
        for (int i = left; i <= right; i++)
            result[(*returnSize)++] = matrix[top][i];

        top++;

        // Top to bottom
        for (int i = top; i <= bottom; i++)
            result[(*returnSize)++] = matrix[i][right];

        right--;

        // Right to left
        if (top <= bottom) {
            for (int i = right; i >= left; i--)
                result[(*returnSize)++] = matrix[bottom][i];

            bottom--;
        }

        // Bottom to top
        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                result[(*returnSize)++] = matrix[i][left];

            left++;
        }
    }

    return result;
}