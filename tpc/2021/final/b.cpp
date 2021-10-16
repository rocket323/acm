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
const int maxl = 2e5 + 10;

struct edge {
    int u, v, w;
} e[maxl];

int t, n, m, p[maxl];
int ans;

int get(int x) {
    if (p[x] == x)
        return x;
    return p[x] = get(p[x]);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            p[i] = i;
        }

        ans = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
            if (e[i].w == 0) {
                int x = get(e[i].u), y = get(e[i].v);
                p[x] = y;
                ans++;
            }
        }

        for (int i = 0; i < m; i++) {
            if (e[i].w > 0) {
                int x = get(e[i].u), y = get(e[i].v);
                if (x != y) {
                    p[x] = y;
                    ans++;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}

