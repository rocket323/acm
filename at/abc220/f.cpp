#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

const int maxl = 2e5 + 10;
int d[maxl], sz[maxl];
long long ans[maxl];
int n, u, v;
vector<int> adj[maxl];

void dfs1(int u, int p, int dd) {
    d[u] = dd;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs1(v, u, dd + 1);
            sz[u] += sz[v];
        }
    }
}

void dfs2(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            ans[v] = ans[u] + n - 2 * sz[v];
            dfs2(v, u);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1, -1, 0);
    for (int i = 2; i <= n; i++)
        ans[1] += d[i];
    dfs2(1, -1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
