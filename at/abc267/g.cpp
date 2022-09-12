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

const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const int maxl = 5050;

int n, k, idx;
int f[2][maxl], a[maxl], c[maxl];

void add(int &a, int b) {
    a = ((ll)a + b) % mod;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n + 1);
    idx = 0;
    memset(f[idx], 0, sizeof(f[idx]));
    f[idx][0] = 1;

    memset(c, 0, sizeof c);
    int same = 0;
    for (int i = 1; i <= n; i++) {
        idx ^= 1;
        same = c[a[i]];
        memset(f[idx], 0, sizeof(f[idx]));
        for (int j = 0; j <= i; j++) {
            if (j > 0)
                f[idx][j] = (ll)f[idx ^ 1][j - 1] * (i - (j - 1) - same) % mod;
            add(f[idx][j], (ll)f[idx ^ 1][j] * (j + same) % mod);
        }
        c[a[i]]++;
    }
    printf("%d\n", f[idx][k + 1]);
    return 0;
}
