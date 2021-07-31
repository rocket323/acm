#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;

const int maxl = 200;
int n, k;
int u, v, w;
int f[maxl][maxl];
int g[maxl];
vector<pair<int, int>> adj[maxl];

void dfs(int u, int pre) {
    for (auto &&kv : adj[u]) {
        if (kv.first != pre) {
            dfs(kv.first, u);
        }
    }
    memset(g, -1, sizeof(g));
    g[0] = 0;
    for (auto &&kv : adj[u]) {
        int v = kv.first, w = kv.second;
        if (v == pre) {
            continue;
        }
        for (int x = k; x >= 0; x--) {
            for (int j = x; j >= 1; j--) {
                if (f[v][j-1] >= 0 && g[x - j] >= 0) {
                    g[x] = max(g[x], g[x - j] + f[v][j-1] + w);
                }
            }
        }
    }
    for (int i = 0; i <= k; i++)
        f[u][i] = g[i];
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n - 1; i ++) {
        scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dfs(1, -1);
    printf("%d\n", f[1][k]);

    return 0;
}
