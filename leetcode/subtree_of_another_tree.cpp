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
    vector<TreeNode*> search(TreeNode* s, int val) {
        vector<TreeNode*> nodes;
        if (s == NULL) {
            return nodes;
        }

        if (s->val == val) {
            nodes.push_back(s);
        }

        vector<TreeNode*> sl = search(s->left, val);
        vector<TreeNode*> sr = search(s->right, val);
        for (const auto& n : sl) {
            nodes.push_back(n);
        }
        for (const auto& n : sr) {
            nodes.push_back(n);
        }

        return nodes;
    }

    bool compare(TreeNode* t1, TreeNode* t2) {
        if (t1 == NULL && t2 == NULL) {
            return true;
        } else if (t1 == NULL || t2 == NULL) {
            return false;
        } else if (t1->val == t2->val) {
            return compare(t1->left, t2->left) && compare(t1->right, t2->right);
        } else {
            return false;
        }
    }

    bool isSubtree(TreeNode* s, TreeNode* t) {
        vector<TreeNode*> sts = search(s, t->val);

        if (sts.empty()) {
            return false;
        }

        for (const auto& st : sts) {
            if (compare(st, t)) {
                return true;
            }
        }

        return false;
    }
};
