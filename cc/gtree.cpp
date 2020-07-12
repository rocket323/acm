#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define maxl 100010

vector<int> adj[maxl];
int c[maxl], top;
int val[maxl], vis[maxl];
int ans[maxl], t, n;
int cnt[maxl];
vector<int> pri[maxl];

int factor(int n) {
    int c = 0;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            c++;
            if (n / i % i == 0)
                return -1;
            n /= i;
        }
    }
    if (n > 1)
        c++;
    return c;
}

void init() {
    memset(c, -1, sizeof c);
    top = 0;
    for (int i = 2; i < maxl; ++i) {
        int cc = factor(i);
        c[i] = cc;
    }

    for (int i = 1; i < maxl; ++i) {
        for (int j = 1; j * j <= i; ++j) {
            if (i % j) continue;
            if (c[j] != -1) pri[i].push_back(j);
            int k = i / j;
            if (k != j && c[k] != -1) pri[i].push_back(k);
        }
        sort(pri[i].begin(), pri[i].end());
    }
}

void dfs(int u) {
    vis[u] = true;
    // 保存在进入节点u之前的统计情况
    int save[70];
    int vv = val[u];
    for (int i = 0; i < pri[vv].size(); ++i) {
        save[i] = cnt[pri[vv][i]];
    }

    for (auto v : adj[u]) {
        if (vis[v]) continue;
        dfs(v);
    }

    for (int i = 0; i < pri[vv].size(); ++i) {
        int p = pri[vv][i];
        int num = cnt[p] - save[i];
        if (c[p] & 1)
            ans[u] += num;
        else
            ans[u] -= num;

        cnt[p]++;
    }
}

int main() {
    scanf("%d", &t);
    init();
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
            adj[i].clear();
        for (int i = 1; i < n; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 1; i <= n; ++i)
            scanf("%d", &val[i]);
        memset(vis, 0, sizeof vis);
        memset(cnt, 0, sizeof cnt);
        memset(ans, 0, sizeof ans);

        dfs(1);

        for (int i = 1; i <= n; ++i)
            printf("%d%c", ans[i], (i == n) ? '\n' : ' ');
    }

    return 0;
}

