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
    TreeNode* construct(vector<int>& nums, int left, int right) {
        if (left > right) {
            return NULL;
        }

        int middle = (left + right) / 2;
        TreeNode* n = new TreeNode(nums[middle]);

        n->left = construct(nums, left, middle - 1);
        n->right = construct(nums, middle + 1, right);

        return n;
    }

    TreeNode* sortedArrayToBST(vector<int>& nums) {
      return construct(nums, 0, nums.size() - 1);
    }
};
