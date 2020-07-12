#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <assert.h>
#define ll long long
using namespace std;
#define maxl 100010
const int mod = 1e9 + 7;

int n, m, t, pw[maxl], k;
vector<int> adj[maxl];
vector<pair<int, int>> edge;

bool adju[maxl], adjv[maxl];

void add(int &a, int b) {
    a += b;
    if (a >= mod)
        a -= mod;
}

int solve2() {
    int ans = 0;
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            if (v < u) continue;

            int n1 = adj[u].size() + adj[v].size() - 2;
            int n2 = m - 1 - n1;

            int t1 = (long long)n1 * pw[n - 3] % mod;
            int t2 = 0;
            if (n2 > 0)
                t2 = (long long)n2 * pw[n - 4] % mod;

            add(ans, pw[n - 2]);
            add(ans, t1);
            add(ans, t2);
        }
    }
    return ans;
}

int solve3() {
    int total = (ll)m * pw[n - 2] % mod;
    int ans = 0;

    for (int i = 0; i < edge.size(); ++i) {
        int u = edge[i].first, v = edge[i].second;
        int n1 = adj[u].size() + adj[v].size() - 2;
        int n2 = m - 1 - n1;

        if (n1 > 0)
            add(ans, (ll)3 * n1 * pw[n - 3] % mod);
        if (n2 > 0)
            add(ans, (ll)3 * n2 * pw[n - 4] % mod);
    }
    add(total, ans);

    ans = 0;
    ll n3 = 0, n4 = 0, n5 = 0, n6 = 0;
    for (int i = 0; i < edge.size(); ++i) {
        int u = edge[i].first, v = edge[i].second;

        for (int x : adj[u]) adju[x] = true;
        for (int x : adj[v]) adjv[x] = true;

        int t3 = 0;
        for (int x : adj[u]) {
            if (x == v) continue;
            int conn = adjv[x];
            if (conn) {
                n3++;
                t3++;
            }

            n4 += (adj[x].size() - conn - 1) * 2;
            int tmp = adj[u].size() + adj[v].size() + adj[x].size() - (2 + conn);
            n5 += m - tmp;
        }

        for (int x : adj[v]) {
            if (x == u) continue;
            int conn = adju[x];
            if (conn) {
                n3++;
                t3++;
            }

            n4 += (adj[x].size() - conn - 1) * 2;

            int tmp = adj[u].size() + adj[v].size() + adj[x].size() - (2 + conn);
            n5 += m - tmp;
        }

        for (int x : adj[u]) adju[x] = false;
        for (int x : adj[v]) adjv[x] = false;

        int tmp1 = adj[u].size() - 1;
        n4 += (ll)tmp1 * (tmp1 - 1);

        int tmp2 = adj[v].size() - 1;
        n4 += (ll)tmp2 * (tmp2 - 1);
        n4 += (ll)tmp1 * tmp2 * 2 - t3;

    }
    n5 *= 3;
    n6 = (ll)m * (m - 1) * (m - 2) - n3 - n4 - n5;
    printf("%lld %lld %lld %lld\n", n3, n4, n5, n6);
    n3 %= mod;
    n4 %= mod;
    n5 %= mod;
    n6 %= mod;
    if (n3 > 0) add(ans, (ll)n3 * pw[n - 3] % mod);
    if (n4 > 0) add(ans, (ll)n4 * pw[n - 4] % mod);
    if (n5 > 0) add(ans, (ll)n5 * pw[n - 5] % mod);
    if (n6 > 0) add(ans, (ll)n6 * pw[n - 6] % mod);

    add(total, ans);
    return total;
}

int main() {
    pw[0] = 1;
    for (int i = 1; i < maxl; ++i)
        pw[i] = (long long)pw[i - 1] * 2 % mod;

    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &k);
        memset(adju, 0, sizeof adju);
        memset(adjv, 0, sizeof adjv);
        edge.clear();
        for (int i = 1; i <= n; ++i)
            adj[i].clear();

        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);

            edge.push_back(make_pair(u, v));
        }

        int ans = 0;
        if (n == 2) {
            ans = m;
        } else if (n > 2) {
            if (k == 1)
                ans = (long long)m * pw[n - 2] % mod;
            else if (k == 2)
                ans = solve2();
            else
                ans = solve3();
        }
        printf("%d\n", ans);
    }

    return 0;
}

