#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;
#define maxl 200010
#define ll long long
const int mod = 1e9 + 7;
 
int n, q;
ll a[maxl];
vector<int> adj[maxl];
int d[maxl];
ll w[maxl];
ll s[maxl * 4];
ll cache[maxl * 4];
 
void dfs(int u, int p, int dep) {
    d[u] = dep;
 
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u, dep + 1);
    }
}
 
int main() {
    while (scanf("%d%d", &n, &q) != EOF) {
        for (int i = 0; i < n; ++i)
            adj[i].clear();
 
        int u, v;
        for (int i = 0; i < n - 1; ++i) {
            scanf("%d%d", &u, &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, -1, 0);
 
        int max_dep = 0;
        memset(s, 0, sizeof s);
        for (int i = 0; i < n; ++i) {
            scanf("%lld", &a[i]);
            
            w[i] = 0;
            for (int j = 0; j < 64; ++j) {
                if (!((a[i] >> j) & 1)) continue;
                w[i] ^= (1LL << j);
            }

            s[d[i]] ^= w[i];
            max_dep = max(max_dep, d[i]);
        }
        ll mask = 1;
        while (mask <= max_dep)
            mask <<= 1;
        mask--;
 
        memset(cache, -1, sizeof cache);
        for (int i = 0; i < q; ++i) {
            ll t;
            scanf("%lld", &t);
 
            ll ans = 0;
            // t--;
            t = (t - 1) & mask;
            if (cache[t] >= 0) {
                printf("%lld\n", cache[t]);
                continue;
            }

            ll tt = (~t) & mask;
            for (int k = tt; k > 0; k = (tt & (k - 1))) {
                ans ^= s[k];
            }
            ans ^= s[0];
 
            cache[t] = ans;
            printf("%lld\n", ans);
        }
    }
 
    return 0;
}

