#include <bits/stdc++.h>

int n, v[10][10], s[10][10];
int x, y, z;
int f[10][10][10][1024];

void move(int prev, int i, int a, int b, int x) {
    if (a > n || b > n)
        return;

    int add = 0;
    if (!(x & (1 << a - 1)))
        add += v[i][a];
    if (a != b && !(x & (1 << b - 1)))
        add += v[i][b];

    int nx = (x | (1 << a - 1) | (1 << b - 1));
    f[i][a][b][nx] = std::max(f[i][a][b][nx], prev + add);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        while (scanf("%d%d%d", &x, &y, &z), (x + y + z)) {
            v[x][y] = z;
        }
        
        memset(f, 0, sizeof f);
        f[1][1][1][1] = v[1][1];

        int ans = 0;
        int mask = (1 << n) - 1;
        for (int i = 1; i <= n; i++) {
            for (int a = 1; a <= n; a++) {
                for (int b = 1; b <= n; b++) {
                    for (int x = 1; x <= mask; x++) {
                        if (i == n && a == n && b == n)
                            ans = std::max(ans, f[i][a][b][x]);

                        move(f[i][a][b][x], i, a + 1, b, x);
                        move(f[i][a][b][x], i, a, b + 1, x);

                        if (i < n)
                            move(f[i][a][b][x], i + 1, a, b, 0);
                    }
                }
            }
        }

        printf("%d\n", ans);
    }

    return 0;
}
