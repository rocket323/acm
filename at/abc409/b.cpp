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

int n, a[maxl];

int calc(int x) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] >= x)
            cnt++;
    }
    return cnt;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    int ans = 0, l = 0, r = 1e9;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (calc(mid) >= mid) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}