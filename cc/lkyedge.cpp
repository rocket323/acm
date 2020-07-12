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
const int maxl = 10010;
const int mod = 1e9 + 7;

struct edge {
    int u, v;
} e[maxl];

int t, m;
int p[maxl];

int find(int v) {
    if (p[v] == v) return v;
    else return p[v] = find(p[v]);
}

void addEdge(int u, int v) {
    int a = find(u), b = find(v);
    if (a != b)
        p[a] = b;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &m);
        int n = 1;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &e[i].u, &e[i].v);
            n = max(n, e[i].u);
            n = max(n, e[i].v);
        }

        for (int i = 0; i < m; ++i) {
            int ans = 0;
            for (int j = 0; j <= i; ++j) {
                for (int k = 1; k <= n; ++k)
                    p[k] = k;

                for (int k = j; k < m; ++k) {
                    if (k == i) continue;
                    addEdge(e[k].u, e[k].v);

                    int a = find(e[i].u), b = find(e[i].v);
                    if (a == b) {
                        int r = k < i ? i : k;
                        ans += (m - r);
                        break;
                    }
                }
            }
            printf("%d%c", ans, (i == m - 1) ? '\n' : ' ');
        }
    }

    return 0;
}

