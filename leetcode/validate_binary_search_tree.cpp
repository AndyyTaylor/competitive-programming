/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include<bits/stdc++.h>

class Solution {
public:
    bool isValidRecurse(TreeNode* root, long min, long max) {
        if (root == NULL) {
            return true;
        }

        if (root->val <= min || root->val >= max) {
            return false;
        }

        return isValidRecurse(root->left, min, root->val) && isValidRecurse(root->right, root->val, max);
    }

    bool isValidBST(TreeNode* root) {
        return isValidRecurse(root, LONG_MIN, LONG_MAX);
    }
};
