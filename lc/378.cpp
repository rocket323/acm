#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getCnt(vector<vector<int>> &a, int x) {
        int n = a.size();
        int r = 0, c = n - 1;
        int ans = 0;

        while (r < n && c >= 0) {
            if (x >= a[r][c]) {
                r++;
                ans += (c + 1);
            } else {
                c--;
            }
        }
        return ans;
    }

    int kthSmallest(vector<vector<int>> &a, int k) {
        int n = a.size();
        int l = a[0][0], r = a[n - 1][n - 1];
        int ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            int cnt = getCnt(a, mid);
            if (cnt >= k) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};

int main() {
    vector<vector<int>> a = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    int k = 8;
    Solution sol;
    printf("%d\n", sol.kthSmallest(a, k));
    return 0;
}
