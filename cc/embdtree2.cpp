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
int min_dep = 0;
int root;
vector<edge> adj[maxl];
vector<int> dd[maxl];

int gao(int u, int d, int dep) {
    int md = 0;
    for (auto &e : adj[u]) {
        if (e.v == d) continue;
        int tmp = gao(e.v, u, dep + 1);
        if (tmp > md)
            md = tmp;
    }
    return md + 1;
}

void dfs(int u, int d, int dep) {
    dd[dep].push_back(u);
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

    min_dep = n + 10;
    for (int i = 1; i <= n; i++) {
        int dep = gao(i, -1, 0);
        if (dep < min_dep) {
            min_dep = dep;
            root = i;
        }
    }

    gap = maxc;
    p[1].x = 0;
    p[1].y = 0;
    dfs(root, -1, 0);

    for (int d = 0; d < n; d++) {
        for (int i = 0; i < dd[d].size(); i++) {
            int u = dd[d][i];
            p[u].y = gap * d;
            p[u].x = i - dd[d].size() / 2;
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d %d\n", p[i].x, p[i].y);
    }

    return 0;
}

