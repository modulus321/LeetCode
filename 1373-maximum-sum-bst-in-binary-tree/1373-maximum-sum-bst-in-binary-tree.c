
#include <limits.h>
#include <stdbool.h>

struct Info {
    bool isBST;
    int min;
    int max;
    int sum;
};

int maxSum;

struct Info dfs(struct TreeNode* root) {
    if (root == NULL) {
        return (struct Info){true, INT_MAX, INT_MIN, 0};
    }

    struct Info left = dfs(root->left);
    struct Info right = dfs(root->right);

    if (left.isBST && right.isBST &&
        root->val > left.max &&
        root->val < right.min) {

        int sum = root->val + left.sum + right.sum;

        if (sum > maxSum)
            maxSum = sum;

        int minVal = root->left ? left.min : root->val;
        int maxVal = root->right ? right.max : root->val;

        return (struct Info){true, minVal, maxVal, sum};
    }

    return (struct Info){false, 0, 0, 0};
}

int maxSumBST(struct TreeNode* root) {
    maxSum = 0;
    dfs(root);
    return maxSum;
}
