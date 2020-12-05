/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void flipTree(TreeNode *n) {
        if (n == NULL) {
            return;
        }

        TreeNode* tmp = n->left;
        n->left = n->right;
        n->right = tmp;

        flipTree(n->left);
        flipTree(n->right);
    }

    bool compare(TreeNode *t1, TreeNode *t2) {
        if (t1 == NULL && t2 == NULL) {
            return true;
        } else if (t1 == NULL || t2 == NULL) {
            return false;
        } else {
            return t1->val == t2->val && compare(t1->left, t2->left) && compare(t1->right, t2->right);
        }
    }

    bool isSymmetric(TreeNode* root) {
        if (root == NULL) {
            return true;
        }

        TreeNode *t1 = root->left;
        flipTree(root->right);
        TreeNode *t2 = root->right;

        return compare(t1, t2);
    }
};
