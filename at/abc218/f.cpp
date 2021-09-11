#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int inf = 0x1f1f1f1f;
const int maxl = 405;
int n, m, in_path[maxl][maxl];
vector<int> adj[maxl];
int u_[maxl * maxl], v_[maxl * maxl];
int dis[maxl][maxl], d[maxl];

struct node {
    int u, d;
};

queue<node> q;

void push(int v, int pre, int dist, bool flag = false) {
    if (d[v] != -1)
        return;
    node nd = {v, dist};
    q.push(nd);
    d[v] = dist;
    if (flag && pre != -1) {
        in_path[pre][v] = 1;
    }
}

void gao(bool flag = false) {
    memset(d, -1, sizeof d);
    push(1, -1, 0, flag);
    while (!q.empty()) {
        node nd = q.front();
        int u = nd.u;
        q.pop();
        for (int v : adj[u]) {
            if (!dis[u][v]) {
                push(v, u, nd.d + 1, flag);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u_[i], &v_[i]);
        adj[u_[i]].push_back(v_[i]);
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            in_path[i][j] = 0;
            dis[i][j] = 0;
        }
    }

    gao(true);

    int dn = d[n];
    for (int i = 1; i <= m; i++) {
        int u = u_[i], v = v_[i];
        if (!in_path[u][v]) {
            printf("%d\n", dn);
        }
        else {
            dis[u][v] = true;
            gao();
            dis[u][v] = false;
            printf("%d\n", d[n]);
        }
    }

    return 0;
}

