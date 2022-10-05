#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, r, a[maxl], cnt[maxl], c0[maxl];
int x[maxl], d[maxl];
vector<int> adj[maxl], adj2[maxl];
int t, idx;

struct node {
    int c1, c, u;
};

bool cmp(const node &a, const node &b) {
    if (a.c1 != b.c1)
        return a.c1 > b.c1;
    if (a.c != b.c)
        return a.c < b.c;
    return a.u > b.u;
}

void dfs(int u, int pre) {
    cnt[u] = (a[u] == 1);
    c0[u] = 1;
    vector<node> vs;
    for (int v : adj[u]) {
        if (v == pre)
            continue;
        dfs(v, u);
        cnt[u] += cnt[v];
        c0[u] += c0[v];
        vs.push_back({cnt[v], c0[v], v});
    }
    sort(vs.begin(), vs.end(), cmp);
    for (auto &&pr : vs) {
        adj2[u].push_back(pr.u);
    }
}

void dfs2(int u) {
    d[u] = idx;
    x[idx++] = a[u];
    for (int v : adj2[u]) {
        dfs2(v);
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &r);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            adj[i].clear();
            adj2[i].clear();
        }
        memset(cnt, 0, sizeof(cnt));
        memset(c0, 0, sizeof(c0));
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(r, -1);
        idx = 1;
        dfs2(r);

        ll c1 = 0;
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            if (x[i] == 0) {
                ans = ans + c1;
            } else {
                c1++;
            }
        }
        cout << ans << endl;
        for (int i = 1; i <= n; i++) {
            printf("%d%c", d[i], i == n ? '\n' : ' ');
        }
    }
    return 0;
}