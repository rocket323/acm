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
const int maxl = 2e6 + 10;

struct node {
    int len, link;
    int ch[26];
} st[maxl * 2];

int cnt, last;
ll ans;
vector<int> adj[maxl];
char s[maxl];
int sz[maxl];

void sam_init() {
    cnt = last = 1;
}

void sam_extend(int c) {
    int cur = ++cnt;
    sz[cur] = 1;
    int p = last;
    st[cur].len = st[last].len + 1;
    last = cur;
    while (p && !st[p].ch[c]) {
        st[p].ch[c] = cur;
        p = st[p].link;
    }
    if (p == 0) {
        st[cur].link = 1;
    } else {
        int q = st[p].ch[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int nq = ++cnt;
            st[nq].len = st[p].len + 1;
            st[nq].link = st[q].link;
            memcpy(st[nq].ch, st[q].ch, sizeof(st[nq].ch));
            while (p && st[p].ch[c] == q) {
                st[p].ch[c] = nq;
                p = st[p].link;
            }
            st[q].link = st[cur].link = nq;
        }
    }
}

void dfs(int u) {
    for (int v : adj[u]) {
        dfs(v);
        sz[u] += sz[v];
    }
    if (sz[u] != 1) {
        ans = max(ans, (ll)sz[u] * st[u].len);
    }
}

int main() {
    scanf("%s", s);
    sam_init();
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        sam_extend(s[i] - 'a');
    for (int i = 1; i <= cnt; i++) {
        adj[st[i].link].push_back(i);
    }
    dfs(1);
    cout << ans << endl;
    return 0;
}