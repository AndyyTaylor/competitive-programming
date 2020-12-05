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
    void inOrder(TreeNode* root, vector<int>* n) {
        if (root == NULL) {
            return;
        }

        inOrder(root->left, n);
        n->push_back(root->val);
        inOrder(root->right, n);

        return;
    }

    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> n = vector<int>();

        inOrder(root, &n);

        return n;
    }
};
