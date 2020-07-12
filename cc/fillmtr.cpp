#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

struct node {
    int x;
    int y;
    int z;
} nd[maxl * 10];

int n, q, t, p[maxl], color[maxl];
map<int, vector<int>> adj;

int find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
}

bool dfs(int u, int c) {
    color[u] = c;

    for (auto v : adj[u]) {
        if (color[v] != -1) {
            if (color[v] != (c ^ 1))
                return false;
            continue;
        }
        if (!dfs(v, c ^ 1))
            return false;
    }
    return true;
}

bool solve() {
    adj.clear();
    for (int i = 0; i < q; ++i) {
        if (nd[i].z == 0) continue;
        int dx = find(nd[i].x), dy = find(nd[i].y);
        if (dx == dy) return false;

        adj[dx].push_back(dy);
        adj[dy].push_back(dx);
    }
    memset(color, -1, sizeof color);
    for (auto kv : adj) {
        int u = kv.first;
        if (color[u] != -1) continue;
        if (!dfs(u, 0))
            return false;
    }
    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &q);
        for (int i = 1; i <= n; ++i)
            p[i] = i;

        for (int i = 0; i < q; ++i) {
            scanf("%d%d%d", &nd[i].x, &nd[i].y, &nd[i].z);
            if (nd[i].z == 0) {
                int dx = find(nd[i].x), dy = find(nd[i].y);
                if (dx != dy)
                    p[dx] = dy;
            }
        }

        bool ans = solve();
        puts(ans ? "yes" : "no");
    }

    return 0;
}


