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
const int maxl = 5e5 + 10;

int n, m, q, p[maxl], ans[maxl];

struct edge {
    int idx, a, b, c;
} e[maxl];

bool cmp(const edge &a, const edge &b) {
    return a.c < b.c;
}

int f(int x) {
    if (p[x] == x)
        return x;
    return p[x] = f(p[x]);
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", &e[i].a, &e[i].b, &e[i].c);
        e[i].idx = i;
    }
    for (int i = 1; i <= q; i++) {
        int j = i + m;
        scanf("%d%d%d", &e[j].a, &e[j].b, &e[j].c);
        e[j].idx = j;
    }
    sort(e + 1, e + m + q + 1, cmp);
    for (int i = 1; i <= n; i++) {
        p[i] = i;
    }
    for (int i = 1; i <= m + q; i++) {
        int u = e[i].a, v = e[i].b;
        int x = f(u), y = f(v);
        if (e[i].idx > m) {
            int idx = e[i].idx - m;
            ans[idx] = (x != y);
        } else {
            p[x] = y;
        }
    }
    for (int i = 1; i <= q; i++) {
        puts(ans[i] > 0 ? "Yes" : "No");
    }
    return 0;
}
