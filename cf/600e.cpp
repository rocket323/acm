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
using vi = vector<int>;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, c[maxl], son[maxl], sz[maxl];
ll ans[maxl];
vector<int> adj[maxl];

struct Set {
    unordered_map<int, int> cnt;
    int max_cnt = 0;
    ll sum = 0;
};

void dfs1(int u, int pre) {
    sz[u] = 1;
    son[u] = 0;
    for (int v : adj[u]) {
        if (v == pre)
            continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (son[u] == 0 || sz[v] > sz[son[u]])
            son[u] = v;
    }
}

void merge(Set &h, Set &l) {
    for (auto &&[k, v] : l.cnt) {
        h.cnt[k] += v;
        if (h.cnt[k] > h.max_cnt) {
            h.max_cnt = h.cnt[k];
            h.sum = k;
        } else if (h.cnt[k] == h.max_cnt) {
            h.sum += (ll)k;
        }
    }
}

Set dfs2(int u, int pre) {
    Set h;
    if (son[u]) {
        h = dfs2(son[u], u);
    }
    for (int v : adj[u]) {
        if (v == son[u] || v == pre)
            continue;
        Set l = dfs2(v, u);
        merge(h, l);
    }
    Set self = {{{c[u], 1}}, 1, c[u]};
    merge(h, self);
    ans[u] = h.sum;
    return h;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
    }
    int u, v;
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
    return 0;
}