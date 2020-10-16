#include <bits/stdc++.h>

int n, m, r, c, ans;
int dr[9] = {0, -2, -1, 1, 2, 2, 1, -1, -2};
int dc[9] = {0, 1, 2, 2, 1, -1, -2, -2, -1};
long long f[30][30];

bool check(int nr, int nc) {
    if (nr < 0 || nr > n)
        return false;
    if (nc < 0 || nc > m)
        return false;

    for (int k = 0; k < 9; k++) {
        if (nr == r + dr[k] && nc == c + dc[k])
            return false;
    }

    return true;
}

int main() {
    while (scanf("%d%d%d%d", &n, &m, &r, &c) != EOF) {
        memset(f, 0, sizeof f);
        f[0][0] = 1;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (f[i][j] == 0)
                    continue;

                if (check(i + 1, j))
                    f[i+1][j] += f[i][j];
                if (check(i, j + 1))
                    f[i][j+1] += f[i][j];
            }
        }
        std::cout << f[n][m] << std::endl;
    }

    return 0;
}
