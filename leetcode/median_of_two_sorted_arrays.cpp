class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> n3;
        int n1_i = 0;
        int n2_i = 0;

        while (n1_i < nums1.size() || n2_i < nums2.size()) {
            if (n1_i >= nums1.size()) {
                n3.push_back(nums2[n2_i++]);
            } else if (n2_i >= nums2.size()) {
                n3.push_back(nums1[n1_i++]);
            } else if (nums1[n1_i] < nums2[n2_i]) {
                n3.push_back(nums1[n1_i++]);
            } else {
                n3.push_back(nums2[n2_i++]);
            }
        }

        for (int i = 0; i < n3.size(); i++) {
            cout << n3[i] << ", ";
        }
        cout << endl;

        double r = n3[(nums1.size() + nums2.size()) / 2];
        if (nums1.size() + nums2.size() > 1 && ((nums1.size() + nums2.size())) % 2 == 0) {
            r += n3[(nums1.size() + nums2.size()) / 2 - 1];
            r /= 2;
        }
        return r;
    }
};
