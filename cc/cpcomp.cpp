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
const int maxl = 100010;
const int mod = 1e9 + 7;

int n, a[maxl];
vector<int> adj[maxl];
int vis[maxl];

int gcd(int a, int b) {
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

void dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (gcd(a[i], a[j]) == 1) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    memset(vis, 0, sizeof vis);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        ans++;
        dfs(i);
    }
    
    printf("%d\n", ans);

    return 0;
}

