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
const int maxl = 1e5 + 10;

int n, x, a[maxl], p[maxl];
int ans, vis[maxl];
vector<int> adj[maxl];

void dfs(int u) {
    vis[u] = 1;
    ans++;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

int main() {
    scanf("%d%d", &n, &x);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        adj[i].push_back(a[i]);
    }
    ans = 0;
    dfs(x);
    printf("%d\n", ans);

    return 0;
}

