#include <stdio.h>
#include <cstring>
#include <vector>
#include <inttypes.h>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;
 
typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;
 
int n, a[maxl];
ll ans[maxl];
int sz[maxl], son[maxl], cnt[maxl];
int mx;
ll sum;
vector<int> adj[maxl];
 
void dfs1(int u, int p) {
    sz[u] = 1;
    son[u] = 0;
    for (int v : adj[u]) {
        if (v == p)
            continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (son[u] == 0 || sz[v] > sz[son[u]])
            son[u] = v;
    }
}
 
void add(int u, int p, int inc, int pp) {
    cnt[a[u]] += inc;
    if (inc > 0 && cnt[a[u]] >= mx) {
        if (cnt[a[u]] > mx) {
            mx = cnt[a[u]];
            sum = 0;
        }
        sum += a[u];
    }
    for (int v : adj[u]) {
        if (v != p && v != pp)
            add(v, u, inc, pp);
    }
}
 
void dfs2(int u, int p, int keep) {
    for (int v : adj[u]) {
        if (v != p && v != son[u]) {
            dfs2(v, u, 0);
        }
    }
    if (son[u])
        dfs2(son[u], u, 1);
 
    add(u, p, 1, son[u]);
    ans[u] = sum;
 
    if (!keep) {
        add(u, p, -1, 0);
        sum = 0, mx = 0;
    }
}
 
int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            adj[i].clear();
        }
 
        for (int i = 1; i < n; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
 
        memset(cnt, 0, sizeof cnt);
        mx = 0;
        dfs1(1, -1);
        dfs2(1, -1, 0);
 
        for (int i = 1; i <= n; i++)
            printf("%I64d%c", ans[i], i == n ? '\n' : ' ');
    }
 
    return 0;
}
