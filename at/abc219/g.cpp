#include <stdio.h>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

const int maxl = 2e5 + 10;
int B, n, m, q, d[maxl];
int u, v;
pii v1[maxl], v2[maxl];
vector<int> adj[maxl];
vector<int> adj2[maxl];

void update(int u) {
    for (int v : adj2[u]) {
        v1[u] = max(v1[u], v2[v]);
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    B = sqrt(n) + 10;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        d[u]++;
        d[v]++;
    }
    for (int u = 1; u <= n; u++) {
        v1[u] = {0, u};
        v2[u] = {0, 0};
        for (int v : adj[u]) {
            if (d[v] > B * 2) {
                adj2[u].push_back(v);
            }
        }
    }

    for (int i = 1; i <= q; i++)  {
        scanf("%d", &u);
        update(u);
        v1[u].first = i;
        if (d[u] <= B * 2) {
            for (int v : adj[u]) {
                v1[v] = max(v1[v], v1[u]);
            }
        } else {
            v2[u] = v1[u];
        }
    }

    for (int i = 1; i <= n; i++) {
        update(i);
        printf("%d%c", v1[i].second, (i == n) ? '\n' : ' ');
    }

    return 0;
}

