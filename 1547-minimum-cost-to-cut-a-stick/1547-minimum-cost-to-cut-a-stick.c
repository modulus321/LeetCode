
#include <stdlib.h>
#include <limits.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minCost(int n, int* cuts, int cutsSize) {
    int m = cutsSize + 2;

    int* arr = malloc(m * sizeof(int));
    arr[0] = 0;
    arr[m - 1] = n;

    for (int i = 0; i < cutsSize; i++) {
        arr[i + 1] = cuts[i];
    }

    qsort(arr, m, sizeof(int), compare);

    int dp[102][102] = {0};

    for (int len = 2; len < m; len++) {
        for (int i = 0; i + len < m; i++) {
            int j = i + len;
            dp[i][j] = INT_MAX;

            for (int k = i + 1; k < j; k++) {
                int cost = arr[j] - arr[i]
                         + dp[i][k] + dp[k][j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    int result = dp[0][m - 1];
    free(arr);

    return result;
}
