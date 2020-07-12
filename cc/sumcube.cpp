#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
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
set<pair<int, int>> g;

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

int vertCnt(vector<int> &v, vector<int> &vv) {
    for (int i = 0; i < v.size(); ++i) {
        vv.push_back(edge[v[i]].first);
        vv.push_back(edge[v[i]].second);
    }
    sort(vv.begin(), vv.end());
    return unique(vv.begin(), vv.end()) - vv.begin();
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

    /*
    for (int i = 0; i < edge.size(); ++i) {
        int u = edge[i].first, v = edge[i].second;

    }
    */

    ans = 0;
    for (int i = 0; i < edge.size(); ++i) {
        for (int j = i + 1; j < edge.size(); ++j) {
            vector<int> p = {i, j};
            vector<int> pp;
            int cnt = vertCnt(p, pp);

            int ac = 0;
            for (int x = 0; x < cnt; ++x)
                for (int y = x + 1; y < cnt; ++y)
                    if (g.count(make_pair(pp[x], pp[y])))
                        ac++;

            int n2 = ac - 2;
            int n1 = 0;
            for (int x = 0; x < cnt; ++x)
                n1 += adj[pp[x]].size();
            n1 -= ac * 2;
            int n0 = m - 2 - n1 - n2;

            if (n0 > 0)
                add(ans, (ll)n0 * pw[n - cnt - 2] % mod);
            if (n1 > 0)
                add(ans, (ll)n1 * pw[n - cnt - 1] % mod);
            if (n2 > 0)
                add(ans, (ll)n2 * pw[n - cnt] % mod);
        }
    }
    add(total, (ll)ans * 2 % mod);
    return total;
}

int solve33() {
    int ans = 0;
    for (int i = 0; i < edge.size(); ++i) {
        add(ans, pw[n - 2]);
        
        for (int j = 0; j < edge.size(); ++j) {
            if (i == j) continue;

            vector<int> p = {i, j};
            vector<int> pp;
            int cnt = vertCnt(p, pp);
            int tmp = (ll)3 * pw[n - cnt] % mod;
            add(ans, tmp);
        }
    }

    for (int i = 0; i < edge.size(); ++i) {
        for (int j = 0; j < edge.size(); ++j) {
            if (i == j) continue;
            for (int k = 0; k < edge.size(); ++k) {
                if (i == k || j == k) continue;

                vector<int> p = {i, j, k};
                vector<int> pp;
                int cnt = vertCnt(p, pp);
                int tmp = pw[n - cnt] % mod;
                add(ans, tmp);
            }
        }
    }

    return ans;
}

int main() {
    pw[0] = 1;
    for (int i = 1; i < maxl; ++i)
        pw[i] = (long long)pw[i - 1] * 2 % mod;

    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &m, &k);
        edge.clear();
        g.clear();
        for (int i = 1; i <= n; ++i)
            adj[i].clear();

        for (int i = 0; i < m; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);

            g.insert(make_pair(u, v));
            g.insert(make_pair(v, u));
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

