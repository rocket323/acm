#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

const int maxl = 1e5 + 10;
int name[maxl];
int n, m, p, root, u, k, top;
vector<int> adj[maxl];
unordered_map<string, int> mp;
char tmp[50];
int dep[maxl], sz[maxl], son[maxl], maxd;

struct query {
    int u, k, idx, ans;
} q[maxl];

vector<query *> e[maxl];
unordered_map<int, int> cnt[maxl];

void dfs1(int u, int d) {
    dep[u] = d;
    sz[u] = 1;
    son[u] = 0;
    maxd = max(maxd, d);
    for (int v : adj[u]) {
        dfs1(v, d + 1);
        sz[u] += sz[v];
        if (son[u] == 0 || sz[v] > sz[son[u]])
            son[u] = v;
    }
}

void add(int u, int inc, int p) {
    int d = dep[u];
    int nm = name[u];
    if (inc > 0) {
        cnt[d][nm]++;
    } else {
        int c = cnt[d][nm];
        if (c == 1)
            cnt[d].erase(nm);
        else
            cnt[d][nm]--;
    }

    for (int v : adj[u]) {
        if (v != p)
            add(v, inc, p);
    }
}

void dfs2(int u, int keep) {
    for (int v : adj[u]) {
        if (v != son[u])
            dfs2(v, 0);
    }

    if (son[u])
        dfs2(son[u], 1);

    add(u, 1, son[u]);

    // answer
    for (auto &q : e[u]) {
        int d = dep[q->u] + q->k;
        q->ans = d > maxd ? 0 : cnt[d].size();
    }

    if (!keep) {
        add(u, -1, 0);
    }
}

int main() {
    scanf("%d", &n);
    top = 0;
    root = n + 1;
    maxd = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%s%d", tmp, &p);
        string s = tmp;
        auto iter = mp.find(s);
        if (iter == mp.end()) {
            mp.insert({s, ++top});
            name[i] = top;
        } else {
            name[i] = iter->second;
        }
        if (p != 0) {
            adj[p].push_back(i);
        } else {
            adj[root].push_back(i);
        }
    }

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &k);
        q[i].u = u;
        q[i].k = k;
        q[i].idx = i;
        e[u].push_back(&q[i]);
    }

    dfs1(root, 0);
    dfs2(root, 0);

    for (int i = 1; i <= m; i++)
        printf("%d\n", q[i].ans);

    return 0;
}
