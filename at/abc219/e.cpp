#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;
int a[10][10], l[10], r[10];
int ans, n;

void dfs(int d, int pl, int pr) {
    if (d == n) {
        ans++;
        return;
    }

    int x = d + 1;
    for (int ll = 0; ll < 4; ll++) {
        for (int rr = ll + 1; rr <= 4; rr++) {
            if (ll <= l[x] && r[x] < rr) {
                if (ll < pr && rr > pl) {
                    dfs(d + 1, ll, rr);
                }
            }
        }
    }
}

int main() {
    for (int i = 0; i < 4; i++) {
        l[i] = inf;
        r[i] = -inf;
        for (int j = 0; j < 4; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 1) {
                l[i] = min(l[i], j);
                r[i] = max(r[i], j);
            }
        }
    }

    n = 4;
    ans = 0;
    dfs(-1, -10, 10);
    printf("%d\n", ans);

    return 0;
}
