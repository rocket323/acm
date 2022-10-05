#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

typedef long long ll;
const int maxl = 500010;
const int mod = 1e9 + 7;
using uii = unordered_map<int, int>;

struct query {
    int idx, d;
    int ans;
};

query q[maxl];
vector<query *> e[maxl];
int n, m, dep[maxl], sz[maxl], son[maxl];
int cnt[maxl][26];
vector<int> adj[maxl];
char s[maxl];

void dfs1(int u, int d) {
    dep[u] = d;
    sz[u] = 1;
    son[u] = 0;
    for (int v : adj[u]) {
        dfs1(v, d + 1);
        sz[u] += sz[v];
        if (son[u] == 0 || sz[v] > sz[son[u]])
            son[u] = v;
    }
}

void merge(uii &h, uii &l) {
    for (auto &&[k, v] : l) {
        h[k] += v;
    }
}

uii dfs2(int u) {
    uii h;
    if (son[u])
        h = dfs2(son[u]);

    for (int v : adj[u]) {
        if (v != son[u]) {
            uii l = dfs2(v);
            merge(h, l);
        }
    }
    uii x = {{dep[u] * 26 + (s[u] - 'a'), 1}};
    merge(h, x);

    // ans the querys
    for (auto &q : e[u]) {
        int d = q->d;
        int odd_cnt = 0;
        for (int i = 0; i < 26; i++) {
            auto iter = h.find(d * 26 + i);
            if (iter != h.end() && (iter->second & 1))
                odd_cnt++;
        }
        q->ans = odd_cnt < 2;
    }
    return h;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 2; i <= n; i++) {
            int u;
            scanf("%d", &u);
            adj[u].push_back(i);
        }
        scanf("%s", s + 1);

        for (int i = 0; i < m; i++) {
            int u, d;
            scanf("%d%d", &u, &d);
            q[i].idx = i;
            q[i].d = d;
            e[u].push_back(&q[i]);
        }

        dfs1(1, 1);
        dfs2(1);

        for (int i = 0; i < m; i++)
            puts(q[i].ans ? "Yes" : "No");
    }

    return 0;
}
