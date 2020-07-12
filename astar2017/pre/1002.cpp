#include <stdio.h>
#include <cstring>
#include <assert.h>
#define maxl 3010

int n, m, ans;
int g[maxl][maxl], del[maxl], w[maxl], in[maxl];

void init() {
    memset(g, 0, sizeof g);
    int a, b, c;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        g[a][b] += c;
        g[b][a] += c;
    }
}

int findMax() {
    int mx = -1, rec = -1;
    for (int i = 1; i <= n; ++i) {
        if (!del[i] && !in[i] && w[i] > mx) {
            mx = w[i];
            rec = i;
        }
    }
    return rec;
}

void update(int k) {
    assert(k >= 1 && k <= n);
    for (int i = 1; i <= n; ++i) {
        if (!del[i] && !in[i]) {
            w[i] += g[i][k];
        }
    }
}

void merge(int s, int t) {
    del[t] = 1;
    for (int i = 1; i <= n; ++i) {
        if (del[i]) continue;
        g[s][i] += g[t][i];
        g[i][s] += g[t][i];
    }
}

void gao() {
    int s, t;
    memset(in, 0, sizeof in);
    in[1] = 1;
    s = 1, t = 0;
    for (int i = 2; i <= n; ++i) w[i] = g[i][1];
    for (int x = 1; x < n; ++x) {
        int k = findMax();
        if (k == -1) break;
        s = t; t = k;
        in[k] = 1;
        update(k);
    }
    merge(s, t);
    if (w[t] < ans) ans = w[t];
}

void solve() {
    memset(del, 0, sizeof del);
    ans = 0x3f3f3f3f;
    for (int i = 1; i < n; ++i) {
        gao();
    }
    printf("%d\n", ans);
}

int main() {

    while (scanf("%d%d", &n, &m) != EOF) {
        init();
        solve();
    }

    return 0;
}

