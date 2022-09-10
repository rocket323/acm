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

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

struct node {
    int k;
    int idx;
};

int n, u, v, m;
int L, R, d[maxl];
int ans[maxl];
int st[maxl], top;
vector<int> adj[maxl];
vector<node> q[maxl];

int findFast(int u, int pre, int dist) {
    d[u] = dist;
    int nd = -1;
    for (int v : adj[u]) {
        if (v == pre)
            continue;
        int x = findFast(v, u, dist + 1);
        if (nd == -1 || d[x] > d[nd])
            nd = x;
    }
    return nd == -1 ? u : nd;
}

void dfs(int u, int pre) {
    st[top++] = u;
    for (auto &&query : q[u]) {
        if (top - 1 >= query.k) {
            ans[query.idx] = st[top - 1 - query.k];
        }
    }
    for (int v : adj[u]) {
        if (v != pre) {
            dfs(v, u);
        }
    }
    top--;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    scanf("%d", &m);
    int k;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &k);
        q[u].push_back({k, i});
    }
    L = findFast(1, -1, 0);
    R = findFast(L, -1, 0);

    memset(ans, -1, sizeof ans);
    dfs(L, -1);
    dfs(R, -1);
    for (int i = 0; i < m; i++)
        printf("%d\n", ans[i]);
    return 0;
}