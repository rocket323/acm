#include <bits/stdc++.h>

int n, k;
int f[300][10][300];
int ans[300][10];

int main() {
    memset(f, 0, sizeof(f));
    f[0][0][0] = 1;

    for (int i = 1; i <= 200; i++) {
        for (int j = 1; j <= 6; j++) {
            for (int k = 1; k <= i; k++) {
                for (int kk = 0; kk <= k; kk++) {
                    f[i][j][k] += f[i - k][j - 1][kk];
                }
                ans[i][j] += f[i][j][k];
            }
        }
    }

    while (scanf("%d%d", &n, &k) != EOF) {
        printf("%d\n", ans[n][k]);
    }
    return 0;
}
