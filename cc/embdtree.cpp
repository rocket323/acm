#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 1010;
const int mod = 1e9 + 7;
int gap = 2;

#define SQ(l) ((l) * (l))

struct edge {
    int v, len;
};

struct pos {
    int x, y;
    int pre, dx;
} p[maxl];

int n;
vector<edge> adj[maxl];
vector<int> dd[maxl];

void dfs(int u, int d, int dep) {
    int lx = p[u].x;
    bool first = true;
    dd[dep].push_back(u);
    for (auto &e : adj[u]) {
        if (e.v == d) continue;

        int dx = lx - p[u].x;;
        if (SQ(e.len) >= SQ(gap)) {
            int dx2 = SQ(e.len) - SQ(gap);
            
            if (dx2 > SQ(dx))
                dx = sqrt(dx2) + 1;
        }
        int x = p[u].x + dx;
        if (x <= lx && !first)
            x = lx + 1;

        first = false;
        p[e.v].x = x;
        p[e.v].y = p[u].y + gap;
        lx = x;

        p[e.v].pre = u;
        p[e.v].dx = x - p[u].x;
    }

    for (auto &e : adj[u]) {
        if (e.v == d) continue;
        dfs(e.v, u, dep + 1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        adj[i].clear();

    int maxc = 0;
    for (int i = 1; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
        if (c > maxc)
            maxc = c;
    }
    // gap = sqrt(maxc);
    gap = 2;
    p[1].x = 0;
    p[1].y = 0;
    dfs(1, -1, 0);

    for (int d = 1; d < n; d++) {
        for (int i = 1; i < dd[d].size(); i++) {
            int u = dd[d][i-1], v = dd[d][i];
            if (p[v].x <= p[u].x)
                p[v].x = p[u].x + 1;

            int pre = p[v].pre;
            if (p[v].x < p[pre].x + p[v].dx)
                p[v].x = p[pre].x + p[v].dx;
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", p[i].x, p[i].y);
        assert(p[i].x >= 0 && p[i].x <= 1e9);
        assert(p[i].y >= 0 && p[i].y <= 1e9);
    }

    return 0;
}

