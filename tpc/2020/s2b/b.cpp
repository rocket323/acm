#include <bits/stdc++.h>

const int inf = 0x3f3f3f3f;
int f[15][15][2][500];
int c[20], vv[20], x[20], y[20];
int n, m, t;

void update(int &a, int b) {
    if (a > b)
        a = b;
}

void solve() {
    for (int v = 400; v >= 0; v--) {
        if (f[n][m][1][v] < inf) {
            printf("%d %d\n", v, f[n][m][1][v]);
            return;
        }
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%d%d%d%d", &c[i], &vv[i], &x[i], &y[i]);
        }

        memset(f, 0x3f, sizeof(f));
        f[0][0][0][0] = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                for (int k = 0; k < 2; k++) {
                    for (int v = 0; v < 400; v++) {
                        if (f[i][j][k][v] >= inf)
                            continue;

                        update(f[i + 1][j][k][v], f[i][j][k][v]);

                        if (j < m) {
                            update(f[i + 1][j + 1][k][v + vv[i + 1]], f[i][j][k][v] + c[i + 1]);

                            if (k == 0) {
                                update(f[i + 1][j + 1][1][v + vv[i + 1] + y[i + 1]],
                                       f[i][j][k][v] + c[i + 1] + x[i + 1]);
                            }
                        }
                    }
                }
            }
        }

        solve();
    }

    return 0;
}
