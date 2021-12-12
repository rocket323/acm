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

vector<int> adj[maxl];
int n, m, u, v, c[5], vis[maxl];
int d[maxl], cnt;

void dfs(int u, int pre) {
    vis[u] = 1;
    cnt++;
    if (d[u] >= 3)
        c[3]++;
    else
        c[d[u]]++;

    if (c[3] > 0)
        return;

    for (int v : adj[u]) {
        if (v != pre && !vis[v]) {
            dfs(v, u);
        }
    }
}

bool gao(int i) {
    memset(c, 0, sizeof c);
    cnt = 0;
    dfs(i, -1);
    if (cnt > 1 && c[1] < 2)
        return false;
    if (c[3] > 0)
        return false;
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        d[u]++;
        d[v]++;
    }

    bool flag = true;
    for (int i = 1; i <= n; i++) {
        if (vis[i])
            continue;
        if (!gao(i)) {
            flag = false;
            break;
        }
    }
    puts(flag ? "Yes" : "No");

    return 0;
}

