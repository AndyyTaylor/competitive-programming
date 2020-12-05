class Solution {
public:
    bool isHappy(int n) {
        unordered_map<int, bool> seen;

        while (n != 1) {
            seen[n] = true;
            int n2 = 0;

            while (n > 0) {
                n2 += pow(n % 10, 2);
                n /= 10;
            }

            if (seen[n2]) {
                return false;
            }

            n = n2;
        }

        return true;
    }
};
