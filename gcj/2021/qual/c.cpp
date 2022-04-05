#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;

int t, n, a[maxl], c;

bool gao() {
    if (c < n - 1)
        return false;
    for (int i = n - 1; i >= 1; i--) {
        int cap = n - i + 1;
        int x = c - (i - 1);
        int y = min(cap, x);
        reverse(a + i, a + i + y);
        c -= y;
    }
    if (c > 0)
        return false;
    return true;
}

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d%d", &n, &c);
        for (int i = 1; i <= n; i++)
            a[i] = i;
        printf("Case #%d: ", tc);
        bool flag = gao();
        if (flag) {
            for (int i = 1; i <= n; i++)
                printf("%d%c", a[i], (i == n) ? '\n' : ' ');
        } else {
            puts("IMPOSSIBLE");
        }
    }
    return 0;
}