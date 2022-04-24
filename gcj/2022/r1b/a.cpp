#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int t;
int n, a[maxl];

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        int mx = 0, l = 1, r = n, ans = 0;
        for (int i = 1; i <= n; i++) {
            int x = l;
            if (a[r] < a[x]) {
                x = r;
                r--;
            } else {
                l++;
            }
            if (a[x] >= mx) {
                ans++;
                mx = a[x];
            }
            // printf("%d %d %d\n", i, mx, a[x]);
        }
        printf("Case #%d: %d\n", tc, ans);
    }
    return 0;
}