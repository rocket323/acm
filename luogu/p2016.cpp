#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;

const int maxl = 1505;
const int inf = 0x3f3f3f3f;
int n, u, v, k;
vector<int> adj[maxl];
int f[maxl][2];

void dfs(int u, int pre) {
    f[u][1] = 1;
    for (int v : adj[u]) {
        if (v == pre)
            continue;
        dfs(v, u);
        f[u][0] += f[v][1];
        f[u][1] += min(f[v][0], f[v][1]);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &u);
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &v);
            adj[u].push_back(v);
        }
    }
    dfs(0, -1);
    printf("%d\n", min(f[0][0], f[0][1]));
    return 0;
}
