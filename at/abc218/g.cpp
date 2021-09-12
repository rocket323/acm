#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;
int n, f[maxl], a[maxl], u, v;
vector<int> adj[maxl];
multiset<int> s, t;

void eval() {
    if (s.size() > 0) {
        auto iter = s.end();
        iter--;
        t.insert(*iter);
        s.erase(iter);
    }

    while (s.size() < t.size()) {
        s.insert(*t.begin());
        t.erase(t.begin());
    }
}

void add(int x) {
    s.insert(x);
    eval();
}

void erase(int x) {
    auto iter = s.end();
    iter--;
    if (*iter < x) t.erase(t.lower_bound(x));
    else s.erase(s.lower_bound(x));
    eval();
}

int mid() {
    auto iter = s.end();
    iter--;
    if (s.size() == t.size() + 1)
        return *iter;
    else
        return (*iter + *t.begin()) / 2;
}

void dfs(int u, int fa, int d) {
    add(a[u]);
    int mn = inf, mx = 0;
    for (int v : adj[u]) {
        if (v == fa)
            continue;
        dfs(v, u, d + 1);
        mn = min(mn, f[v]);
        mx = max(mx, f[v]);
    }
    if (mx == 0) {
        f[u] = mid();
    } else if (d % 2 == 0) {
        f[u] = mx;
    } else {
        f[u] = mn;
    }
    erase(a[u]);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            adj[i].clear();
        }
        for (int i = 0; i < n - 1; i++) {
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, -1, 0);
        printf("%d\n", f[1]);
    }
    return 0;
}

