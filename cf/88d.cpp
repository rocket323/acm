#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, a[maxl], f[maxl];

int dp(int m) {
    for (int i = 1; i <= n; i++) {
        if (a[i] > m)
            a[i] = -inf;
        f[i] = -inf;
    }
    f[0] = 0;
    int ans = -inf;
    for (int i = 1; i <= n; i++) {
        f[i] = max(a[i], f[i - 1] + a[i]);
        ans = max(ans, f[i]);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int ans = -inf;
    for (int i = 30; i >= -30; i--) {
        int tmp = dp(i) - i;
        ans = max(ans, tmp);
    }
    printf("%d\n", ans);
    return 0;
}
