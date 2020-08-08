#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;
 
typedef long long ll;
const int maxl = 500010;
const int mod = 1e9 + 7;
 
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
 
void add(int u, int inc, int p) {
    int x = s[u] - 'a';
    cnt[dep[u]][x] += inc;
 
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
 
    // ans the querys
    for (auto &q : e[u]) {
        int d = q->d;
        int odd_cnt = 0;
        for (int i = 0; i < 26; i++) {
            if (cnt[d][i] & 1)
                odd_cnt++;
        }
        q->ans = odd_cnt < 2;
    }
 
    if (!keep) {
        add(u, -1, 0);
    }
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
        dfs2(1, 0);
 
        for (int i = 0; i < m; i++)
            puts(q[i].ans ? "Yes" : "No");
    }
 
    return 0;
}
