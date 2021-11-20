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

int n, t[maxl], k[maxl], d[maxl];
vector<int> adj[maxl];
vector<int> adj2[maxl];
int v, st[maxl], top, p[maxl];
int vis[maxl];
ll ans;

void dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (!vis[v])
            dfs(v);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &t[i], &k[i]);
        for (int j = 0; j < k[i]; j++) {
            scanf("%d", &v);
            adj[i].push_back(v);
        }
    }

    dfs(n);

    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            ans += (ll)t[i];
        }
    }
    cout << ans << endl;

    return 0;
}

