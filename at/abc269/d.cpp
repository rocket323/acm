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

int n, x[maxl], y[maxl], p[maxl];
int d1[6] = {-1, -1, 0, 0, 1, 1};
int d2[6] = {-1, 0, -1, 1, 0, 1};

bool check(int i, int j) {
    for (int t = 0; t < 6; t++) {
        if (x[i] + d1[t] == x[j] && y[i] + d2[t] == y[j])
            return true;
    }
    return false;
}

int ffind(int x) {
    if (p[x] == x)
        return x;
    return p[x] = ffind(p[x]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
        p[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            if (!check(i, j))
                continue;

            int ii = ffind(i), jj = ffind(j);
            p[ii] = jj;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (p[i] == i)
            ans++;
    }
    printf("%d\n", ans);

    return 0;
}