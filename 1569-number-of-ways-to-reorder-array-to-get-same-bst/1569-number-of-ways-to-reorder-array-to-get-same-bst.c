
#include <stdlib.h>

#define MOD 1000000007

long long comb[1001][1001];

long long dfs(int* nums, int n) {
    if (n <= 2)
        return 1;

    int* left = malloc(n * sizeof(int));
    int* right = malloc(n * sizeof(int));

    int l = 0, r = 0;

    for (int i = 1; i < n; i++) {
        if (nums[i] < nums[0])
            left[l++] = nums[i];
        else
            right[r++] = nums[i];
    }

    long long leftWays = dfs(left, l);
    long long rightWays = dfs(right, r);

    long long ways = comb[n - 1][l];
    ways = ways * leftWays % MOD;
    ways = ways * rightWays % MOD;

    free(left);
    free(right);

    return ways;
}

int numOfWays(int* nums, int numsSize) {
    for (int i = 0; i <= numsSize; i++) {
        comb[i][0] = 1;
        comb[i][i] = 1;

        for (int j = 1; j < i; j++) {
            comb[i][j] = (comb[i - 1][j - 1] +
                          comb[i - 1][j]) % MOD;
        }
    }

    return (int)((dfs(nums, numsSize) - 1 + MOD) % MOD);
}
