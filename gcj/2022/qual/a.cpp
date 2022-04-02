#include <bits/stdc++.h>

int t, r, c;
char g[100][100];

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d%d", &r, &c);
        g[0][0] = '.';
        for (int j = 1; j < 2 * c + 1; j++) {
            g[0][j] = (j & 1) ? '-' : '+';
        }
        int cr = 0;
        for (int i = 0; i < r; i++) {
            ++cr;
            for (int j = 0; j < 2 * c + 1; j++) {
                g[cr][j] = (j & 1) ? '.' : '|';
            }
            ++cr;
            for (int j = 0; j < 2 * c + 1; j++) {
                g[cr][j] = (j & 1) ? '-' : '+';
            }
        }
        g[0][0] = g[0][1] = g[1][0] = g[1][1] = '.';
        printf("Case #%d:\n", tc);
        for (int i = 0; i < 2 * r + 1; i++) {
            for (int j = 0; j < 2 * c + 1; j++) {
                printf("%c", g[i][j]);
                if (j == 2 * c)
                    puts("");
            }
        }
    }
    return 0;
}