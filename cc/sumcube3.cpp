#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_set>
#include <iostream>
#include <set>
#include <algorithm>
#include <sstream>
#include <assert.h>
#include <math.h>
#define ll long long
using namespace std;
#define maxl 200010
const int mod = 1e9 + 7;
 
int n, m, t, pw[maxl], k;
vector<int> adj[maxl];
vector<pair<int, int>> edge;
int d[maxl];
int BS;
int b[maxl], top;
// unordered_set<ll> g;
set<pair<int, int>> g;
 
void add(int &a, int b) {
    a += b;
    if (a >= mod)
        a -= mod;
}

bool isConn(int u, int v) {
    return g.count(make_pair(u, v));
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
    ll p4 = 0;

    // calc n3
    for (int i = 0; i < top; ++i) {
        for (int j = i + 1; j < top; ++j) {
            if (!isConn(b[i], b[j])) continue;
            for (int k = j + 1; k < top; ++k) {
                if (!isConn(b[i], b[k])) continue;
                if (!isConn(b[j], b[k])) continue;

                n3 += 6LL;
                // printf("xx %lld\n", n3);
            }
        }
    }
    for (int u = 1; u <= n; ++u) {
        if (d[u] >= BS) continue;
        for (int i = 0; i < adj[u].size(); ++i) {
            for (int j = i + 1; j < adj[u].size(); ++j) {
                int v = adj[u][i], x = adj[u][j];
                int conn = isConn(v, x);
                if (!conn) continue;

                int t = u;
                if (d[v] < BS) t = min(t, v);
                if (d[x] < BS) t = min(t, x);

                n3 += 2LL;

                if (u == t) {
                    if (d[v] >= BS)
                        n3 += 2LL;
                    if (d[x] >= BS)
                        n3 += 2LL;
                }
            }
        }
    }

    // calc n4
    for (int i = 0; i < edge.size(); ++i) {
        int u = edge[i].first, v = edge[i].second;
        int t1 = adj[u].size() - 1;
        int t2 = adj[v].size() - 1;
        n4 += (ll)t1 * t2 * 2;
        p4 += (ll)t1 * t2 * 2;
    }
    n4 -= n3;
    p4 -= n3;

    n4 *= 3;
    p4 *= 3;
    for (int i = 1; i <= n; ++i) {
        ll t = adj[i].size();
        n4 += t * (t - 1) * (t - 2);
    }

    for (int x = 1; x <= n; ++x) {
        ll t = adj[x].size();
        ll t1 = t * (t - 1) * (t - 2);
        ll t2 = t * (t - 1) * (m - t) * 3;
        n5 += t1 + t2;
    }
    n5 -= n4 + 3 * n3 + p4;
 
    n6 = (ll)m * (m - 1) * (m - 2) - n3 - n4 - n5;
    // printf("%lld %lld %lld %lld\n", n3, n4, n5, n6);
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
        memset(d, 0, sizeof d);
        BS = (sqrt(m) + 2);
        edge.clear();
        g.clear();
        for (int i = 1; i <= n; ++i)
            adj[i].clear();
 
        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
            d[u]++;
            d[v]++;
 
            edge.push_back(make_pair(u, v));

            g.insert(make_pair(u, v));
            g.insert(make_pair(v, u));
        }
        top = 0;
        for (int i = 1; i <= n; ++i) {
            if (d[i] >= BS)
                b[top++] = i;
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

