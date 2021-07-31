#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;

const int maxl = 6010;
int n, k, u, v;
int f[maxl][2], s[maxl], p[maxl];
vector<int> adj[maxl];

void dfs(int u, int pre) {
    f[u][1] = s[u];
    for (int v : adj[u]) {
        dfs(v, u);
        f[u][0] += max(0, max(f[v][0], f[v][1]));
        f[u][1] += max(0, f[v][0]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &s[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u, &v);
        adj[v].push_back(u);
        p[u] = v;
    }
    int nd = 0;
    for (int i = 1; i <= n; i++) {
        if (p[i] == 0)
            nd = i;
    }
    dfs(nd, 0);
    printf("%d\n", max(f[nd][0], f[nd][1]));
    return 0;
}
