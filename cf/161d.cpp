#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 5e4 + 10;

int n, k, u, v;
vector<int> adj[maxl];
ll d[maxl][505], f[maxl][505];
ll ans = 0;

void dfs(int u, int pre) {
    for (int i = 0; i <= k; i++)
        d[u][i] = 0;
    d[u][0] = 1;

    for (int v : adj[u]) {
        if (v == pre)
            continue;
        dfs(v, u);
        for (int i = 0; i < k; i++) {
            d[u][i + 1] += d[v][i];
        }
    }
}

void dfs2(int u, int pre) {
    ll sum = 0;
    for (int v : adj[u]) {
        if (v == pre)
            continue;
        dfs2(v, u);
        for (int i = 1; i < k; i++) {
            ll tmp = d[v][i - 1] * (d[u][k - i] - d[v][k - i - 1]);
            sum += tmp;
        }
    }
    sum /= 2;
    sum += d[u][k];
    ans += sum;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    dfs2(1, 0);
    cout << ans << endl;
    return 0;
}