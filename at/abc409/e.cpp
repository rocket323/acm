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
const int maxl = 2e5 + 10;

int n, x[maxl], s[maxl];
ll ans;
vector<pair<int, int>> adj[maxl];

void dfs(int u, int pre, int pre_w) {
    s[u] = x[u];
    for (auto &&[v, w] : adj[u]) {
        if (v == pre)
            continue;
        dfs(v, u, w);
        s[u] += s[v];
    }
    if (s[u] != 0) {
        ans += (ll)abs(s[u]) * pre_w;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x[i]);
    }
    for (int i = 1; i < n; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    dfs(1, 0, 0);
    cout << ans << endl;
    return 0;
}
