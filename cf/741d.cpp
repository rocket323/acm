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
const int maxl = 5e5 + 10;

int n, p, sz[maxl], h[maxl];
char c[maxl];
int mask[maxl], ans[maxl];
vector<int> adj[maxl];

struct Set {
    unordered_map<int, int> mh;
    int ans = 0;
};

void dfs1(int u, int dep, int m) {
    sz[u] = 1;
    h[u] = dep;
    int x = 1 << (c[u] - 'a');
    mask[u] = m ^ x;
    for (auto &&v : adj[u]) {
        dfs1(v, dep + 1, mask[u]);
        sz[u] += sz[v];
        if (sz[v] > sz[adj[u][0]])
            swap(adj[u][0], v);
    }
}

void merge(Set &s, const Set &l, int u) {
    int tot = 'v' - 'a';
    for (auto &&[msk, height] : l.mh) {
        for (int i = -1; i <= tot; i++) {
            int target = i == -1 ? 0 : (1 << i);
            int x = msk ^ target;
            auto iter = s.mh.find(x);
            if (iter == s.mh.end())
                continue;
            int tmp = iter->second + height - 2 * h[u];
            s.ans = max(s.ans, tmp);
        }
    }
    for (auto &&[msk, height] : l.mh) {
        s.mh[msk] = max(s.mh[msk], height);
    }
    s.ans = max(s.ans, l.ans);
}

Set dfs2(int u) {
    Set s = adj[u].empty() ? Set{} : dfs2(adj[u][0]);
    for (int i = 1; i < adj[u].size(); i++) {
        merge(s, dfs2(adj[u][i]), u);
    }
    Set x = {{{mask[u], h[u]}}, 0};
    merge(s, x, u);
    ans[u] = s.ans;
    return s;
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d %c", &p, &c[i]);
        adj[p].push_back(i);
    }
    dfs1(1, 0, 0);
    dfs2(1);
    for (int i = 1; i <= n; i++) {
        printf("%d%c", ans[i], i == n ? '\n' : ' ');
    }
    return 0;
}