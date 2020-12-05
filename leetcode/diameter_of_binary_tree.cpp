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
    vector<int> getDiam(TreeNode* n) {
        if (n == NULL) {
            vector<int> v;
            v.push_back(-1);
            v.push_back(0);

            return v;
        }

        vector<int> l = getDiam(n->left);
        vector<int> r = getDiam(n->right);

        int curDiam = l[0] + r[0] + 2;
        int maxPath = max(l[0] + 1, r[0] + 1);
        int maxDiam = max(max(curDiam, l[1]), r[1]);

        vector<int> v;
        v.push_back(maxPath);
        v.push_back(maxDiam);

        // cout << n->val << " - " << maxPath << ", " << maxDiam << endl;

        return v;
    }
    int diameterOfBinaryTree(TreeNode* root) {
        vector<int> n = getDiam(root);

        return n[1];
    }
};
