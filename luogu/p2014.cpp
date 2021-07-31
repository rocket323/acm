#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;

const int maxl = 305;
int n, m, s[maxl], k;
vector<int> adj[maxl];
int f[maxl][maxl];

void dfs(int u) {
    for (int v : adj[u]) {
        dfs(v);
    }

    memset(f[u], -1, sizeof(f[u]));
    f[u][0] = 0;
    f[u][1] = s[u];

    for (int v : adj[u]) {
        for (int i = m + 1; i >= 1; i--) {
            for (int j = i-1; j >= 0; j--) {
                if (f[u][i-j] < 0 || f[v][j] < 0)
                    continue;
                f[u][i] = max(f[u][i], f[u][i-j] + f[v][j]);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &k, &s[i]);
        adj[k].push_back(i);
    }

    dfs(0);
    printf("%d\n", f[0][m + 1]);

    return 0;
}
