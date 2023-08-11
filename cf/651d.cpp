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

int n, k, a[maxl], f[maxl];

bool gao(int limit, int start, int end, int len) {
    memset(f, -1, sizeof(f));
    f[start] = a[start] <= limit ? 1 : 0;
    if (f[start] >= len)
        return true;
    for (int i = start + 1; i <= end; i++) {
        f[i] = f[i - 1];
        if (a[i] <= limit) {
            f[i] = max(f[i], 1);
            if (i - 2 >= start) {
                f[i] = max(f[i], f[i - 2] + 1);
            }
        }
        if (f[i] >= len)
            return true;
    }
    return false;
}

bool check(int limit) {
    if (k & 1) {
        if (gao(limit, 1, n, (k + 1) / 2))
            return true;
        if (gao(limit, 2, n - 1, k / 2))
            return true;
        return false;
    } else {
        if (gao(limit, 1, n - 1, (k + 1) / 2))
            return true;
        if (gao(limit, 2, n, k / 2))
            return true;
        return false;
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int l = 1, r = 1e9, ans = inf;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
