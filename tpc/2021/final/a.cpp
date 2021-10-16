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
const int mod = 1e9 + 7;

int n, a[maxl], b[maxl], f[maxl], c[maxl];
int t;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        memset(b, 0, sizeof b);
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            b[i] = max(a[i], b[i-1]);
        }
        c[n+1] = inf;
        for (int i = n; i >= 1; i--) {
            c[i] = min(c[i+1], a[i]);
        }

        f[0] = 1;
        for (int i = 1; i <= n; i++) {
            if (i > 1)
                f[i] = f[i-1];
            if (a[i] >= b[i-1] && c[i] >= b[i-1])
                f[i] = (f[i] + f[i-1]) % mod;
            // printf("%d %d %d\n", i, a[i], f[i]);
        }
        printf("%d\n", f[n]);
    }

    return 0;
}

