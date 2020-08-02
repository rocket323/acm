#include <stdio.h>
#include <vector>
#include <iostream>

class Solution {
public:
    int reverse(int x) {
        int sign = 1;
        long long xx = x;
        if (xx < 0) {
            sign = -1;
            xx = -xx;
        }

        std::vector<int> v;
        while (xx) {
            v.push_back(xx % 10);
            xx /= 10;
        }
        long long ans = 0;
        for (int n : v) {
            ans = ans * 10LL + n;
        }
        ans = sign * ans;
        long long inf = 1LL << 31;
        if (ans > inf - 1 || ans < -inf)
            return 0;
        return ans;
    }
};

int main() {
    Solution sol;
    int n = 1563847412;
    std::cout << sol.reverse(n) << std::endl;
}
