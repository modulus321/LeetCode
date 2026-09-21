#include <stdbool.h>
#include <limits.h>

bool check(struct TreeNode* root, long min, long max) {

    if (root == NULL)
        return true;

    if (root->val <= min || root->val >= max)
        return false;

    return check(root->left, min, root->val) &&
           check(root->right, root->val, max);
}

bool isValidBST(struct TreeNode* root) {
    return check(root, LONG_MIN, LONG_MAX);
}