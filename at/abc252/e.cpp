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

const ll inf = 1e17;
const int maxl = 2e5 + 10;

int n, m, a, b, c;
int vis[maxl];
ll d[maxl];

struct node {
    int u;
    ll d;
    int idx;
};

struct cmp {
    bool operator()(const node &a, const node &b) {
        return a.d > b.d;
    }
};

struct edge {
    int v, c, idx;
};
vector<edge> adj[maxl];

priority_queue<node, vector<node>, cmp> q;
int ans[maxl];

void push(int u, ll d, int idx) {
    if (vis[u])
        return;
    node nd = {u, d, idx};
    q.push(nd);
}

void prim() {
    for (int i = 1; i <= n; i++) {
        d[i] = inf;
        vis[i] = 0;
    }
    push(1, 0, 0);
    d[1] = 0;
    while (!q.empty()) {
        node nd = q.top();
        q.pop();
        if (vis[nd.u])
            continue;
        ans[nd.idx] = 1;
        vis[nd.u] = 1;
        for (auto &&edg : adj[nd.u]) {
            int v = edg.v;
            ll dist = edg.c;
            int idx = edg.idx;
            if (!vis[v] && d[v] > nd.d + dist) {
                d[v] = nd.d + dist;
                push(v, d[v], idx);
            }
        }
    }
    vector<int> x;
    for (int i = 1; i <= m; i++) {
        if (ans[i])
            x.push_back(i);
    }
    for (int i = 0; i < x.size(); i++) {
        printf("%d%c", x[i], (i == x.size() - 1) ? '\n' : ' ');
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        adj[a].push_back({b, c, i + 1});
        adj[b].push_back({a, c, i + 1});
    }

    prim();

    return 0;
}