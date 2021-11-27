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

int n, m, p[maxl], ans[maxl], comp;
vector<int> adj[maxl];

int ffind(int x) {
    if (p[x] == x)
        return x;
    return p[x] = ffind(p[x]);
}

void add(int u) {
    comp++;
    for (int v : adj[u]) {
        if (v < u)
            continue;

        int x = ffind(u);
        int y = ffind(v);
        if (x != y) {
            p[x] = y;
            comp--;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++)
        p[i] = i;
    comp = 0;
    ans[n] = 0;
    for (int i = n - 1; i >= 1; i--) {
        add(i + 1);
        ans[i] = comp;
    }
    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
    return 0;
}

