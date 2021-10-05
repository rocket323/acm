#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int mod = 998244353;
const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, u, v;
int x, y, d[maxl][5], D, blk[maxl], block;
vector<int> adj[maxl];
vector<int> ans;

int findd(int idx) {
    int x = 0;
    for (int i = 1; i <= n; i++) {
        if (x == 0 || d[x][idx] < d[i][idx])
            x = i;
    }
    return x;
}

void dfs(int u, int p, int dep, int idx) {
    d[u][idx] = dep;
    blk[u] = block;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, dep + 1, idx);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 5; j++)
            d[i][j] = -1;
    }

    dfs(1, -1, 0, 0);
    int x = findd(0);

    for (int i = 1; i <= n; i++)
        d[i][0] = -1;

    dfs(x, -1, 0, 0);
    int y = findd(0);
    D = d[y][0];

    dfs(y, -1, 0, 1);

    if (D % 2 == 1) {
        int a = 0, b = 0;
        for (int i = 1; i <= n; i++) {
            if (d[i][0] == D / 2 && d[i][1] == D / 2 + 1) a = i;
            if (d[i][1] == D / 2 && d[i][0] == D / 2 + 1) b = i;
        }

        dfs(a, b, 0, 2);
        dfs(b, a, 0, 3);
        int c1 = 0, c2 = 0;
        for (int i = 1; i <= n; i++) {
            if (d[i][2] == D / 2) c1++;
            if (d[i][3] == D / 2) c2++;
        }
        ans.push_back(c1);
        ans.push_back(c2);
    } else {
        int c = 0;
        for (int i = 1; i <= n; i++) {
            if (d[i][0] == D / 2 && d[i][1] == D / 2) c = i;
        }

        for (int v : adj[c]) {
            block = v;
            dfs(v, c, 1, 2);
        }

        unordered_map<int, int> mp;
        for (int i = 1; i <= n; i++) {
            if (d[i][2] == D / 2)
                mp[blk[i]]++;
        }
        for (auto &kv : mp) {
            ans.push_back(kv.second);
        }
    }

    int cnt = 1;
    for (int x : ans) {
        cnt = ((ll)cnt * (x + 1)) % mod;
    }
    for (int x : ans) {
        cnt = (cnt + mod - x) % mod;
    }
    cnt = (cnt + mod - 1) % mod;
    printf("%d\n", cnt);

    return 0;
}

