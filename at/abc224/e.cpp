#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 3e5 + 10;

struct node {
    int r, c, a;
} p[maxl];

int h, w, n, d[maxl];
int st[maxl], top;
vector<int> adj[maxl];
vector<int> r[maxl];
vector<int> c[maxl];
int sl[maxl], ans[maxl];

bool cmp(int i, int j) {
    return p[i].a < p[j].a;
}

void add(int i, int j) {
    adj[i].push_back(j);
    d[j]++;
}

int main() {
    scanf("%d%d%d", &h, &w, &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &p[i].r, &p[i].c, &p[i].a);
        r[p[i].r].push_back(i);
        c[p[i].c].push_back(i);
    }
    for (int i = 1; i <= h; i++) {
        if (r[i].size() == 0)
            continue;
        sort(r[i].begin(), r[i].end(), cmp);
        int x = 0;
        for (int j = 0; j < r[i].size() - 1; j++) {
            while (p[r[i][x]].a == p[r[i][j]].a && x + 1 < r[i].size())
                x++;
            if (p[r[i][x]].a > p[r[i][j]].a) {
                int y = x;
                while (y < r[i].size() && p[r[i][x]].a == p[r[i][y]].a) {
                    add(r[i][j], r[i][y]);
                    y++;
                }
            }
        }
    }
    for (int i = 1; i <= w; i++) {
        if (c[i].size() == 0)
            continue;
        sort(c[i].begin(), c[i].end(), cmp);
        int x = 0;
        for (int j = 0; j < c[i].size() - 1; j++) {
            while (p[c[i][x]].a == p[c[i][j]].a && x + 1 < c[i].size())
                x++;

            if (p[c[i][x]].a > p[c[i][j]].a) {
                int y = x;
                while (y < c[i].size() && p[c[i][x]].a == p[c[i][y]].a) {
                    add(c[i][j], c[i][y]);
                    y++;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (d[i] == 0)
            st[top++] = i;
    }

    for (int i = 0; i < n; i++) {
        int u = st[--top];
        sl[i] = u;
        for (int v : adj[u]) {
            d[v]--;
            if (d[v] == 0)
                st[top++] = v;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        int u = sl[i];
        for (int v : adj[u]) {
            ans[u] = max(ans[u], ans[v] + 1);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}

