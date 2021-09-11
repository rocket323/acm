#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;
const int maxl = 2e5 + 10;
int n, m, p[maxl];

struct edge {
    int u, v, w;
} e[maxl];

bool cmp(const edge &a, const edge &b) {
    return a.w < b.w;
}

int ffind(int x) {
    if (p[x] == x)
        return x;
    return p[x] = ffind(p[x]);
}

void add(int u, int v) {
    int p1 = ffind(u), p2 = ffind(v);
    p[p1] = p2;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++)
            p[i] = i;

        ll sum = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
            if (e[i].w > 0) {
                sum = sum + e[i].w;
            }
        }

        sort(e, e + m, cmp);
        ll x = 0;
        for (int i = 0; i < m; i++) {
            if (e[i].w < 0) {
                add(e[i].u, e[i].v);
            } else {
                int p1 = ffind(e[i].u), p2 = ffind(e[i].v);
                if (p1 != p2) {
                    add(e[i].u, e[i].v);
                    x += e[i].w;
                }
            }
        }

        cout << sum - x << endl;
    }
    return 0;
}

