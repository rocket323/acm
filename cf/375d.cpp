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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, m, c[maxl], sz[maxl], son[maxl], ans[maxl];
vector<int> adj[maxl];

struct node {
    int k;
    int idx;
};
vector<node> query[maxl];

struct Set {
    // color => cnt
    unordered_map<int, int> col;
    // (cnt, col)
    ordered_set<pair<int, int>> st;

    Set() {
    }
    Set(int color) {
        add(color, 1);
    }
    void add(int color, int count) {
        auto iter = col.find(color);
        int cnt = 0;
        if (iter != col.end()) {
            st.erase(make_pair(iter->second, color));
            iter->second += count;
            cnt = iter->second;
        } else {
            col[color] += count;
            cnt = count;
        }
        st.insert(make_pair(cnt, color));
    }
    int get(int k) {
        int count = st.order_of_key({k, 0});
        return st.size() - count;
    }
};

void dfs1(int u, int pre) {
    sz[u] = 1;
    for (auto &&v : adj[u]) {
        if (v == pre)
            continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (son[u] == 0 || sz[v] > sz[son[u]])
            son[u] = v;
    }
}

void merge(Set &s, const Set &l) {
    for (auto &&[col, cnt] : l.col) {
        s.add(col, cnt);
    }
}

Set dfs2(int u, int pre) {
    Set s = !son[u] ? Set{} : dfs2(son[u], u);
    for (int v : adj[u]) {
        if (v != pre && v != son[u])
            merge(s, dfs2(v, u));
    }
    Set x(c[u]);
    merge(s, x);
    for (auto &&q : query[u]) {
        ans[q.idx] = s.get(q.k);
    }
    return s;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &c[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < m; i++) {
        int x, k;
        scanf("%d%d", &x, &k);
        query[x].push_back({k, i});
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for (int i = 0; i < m; i++)
        printf("%d\n", ans[i]);
    return 0;
}
