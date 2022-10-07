#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f
#define maxl 20
using ll = long long;

int list[maxl], top, n, m, g[maxl][maxl];
int sum, f[70000], d[maxl];

void init() {
    sum = 0;
    memset(g, 0x3f, sizeof g);
    memset(d, 0, sizeof d);
    top = 0;

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        // scanf("%d%d%d", &a, &b, &c);
        cin >> a >> b >> c;
        a--;
        b--;
        d[a]++;
        d[b]++;
        g[a][b] = g[b][a] = min(g[a][b], c);
        sum += c;
    }
    for (int i = 0; i < n; ++i)
        if (d[i] & 1) {
            list[top++] = i;
        }
}

int contain(int s, int a) {
    return s & (1 << a);
}

int solve() {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
        }
    }
    for (int i = 0; i < n; i++)
        g[i][i] = 0;

    for (int i = 0; i < n; i++) {
        if (d[i] && g[i][0] >= INF)
            return -1;
    }

    memset(f, 0x3f, sizeof f);
    f[0] = 0;

    int mask = (1 << top) - 1;
    for (int i = 0; i <= mask; ++i) {
        if (f[i] >= INF)
            continue;

        for (int a_ = 0; a_ < top; ++a_) {
            if (contain(i, a_))
                continue;
            for (int b_ = 0; b_ < top; ++b_) {
                if (contain(i, b_) || a_ == b_)
                    continue;
                int a = list[a_];
                int b = list[b_];
                if (g[a][b] >= INF)
                    continue;

                int tmp = i | (1 << a_) | (1 << b_);
                f[tmp] = min(f[tmp], f[i] + g[a][b]);
            }
        }
    }
    return f[mask] >= INF ? -1 : f[mask] + sum;
}

int main() {
    while (cin >> n >> m) {
        init();
        cout << solve() << endl;
    }
    return 0;
}
