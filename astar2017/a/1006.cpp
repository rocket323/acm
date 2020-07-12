#include <stdio.h>
#include <cstring>
#define maxl 201

char s[maxl][maxl];
bool vis[maxl][maxl];
int n, m;

int dr[4] = {0, 1, 0, -1};
int dc[4] = {1, 0, -1, 0};

void dfs(int r, int c, char ch) {
    vis[r][c] = 1;
    for (int k = 0; k < 4; ++k) {
        int rr = r + dr[k];
        int cc = c + dc[k];
        if (rr < 0 || rr > n + 1) continue;
        if (cc < 0 || cc > m + 1) continue;
        if (vis[rr][cc]) continue;
        if (ch != s[rr][cc]) continue;

        dfs(rr, cc, ch);
    }
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        memset(vis, 0, sizeof vis);
        for (int i = 0; i <= n+1; ++i)
            for (int j = 0; j <= m+1; ++j)
                s[i][j] = '0';

        for (int i = 1; i <= n; ++i) {
            scanf("%s", s[i] + 1);
            s[i][0] = '0';
            s[i][m+1] = '0';
        }

        /*
        for (int i = 0; i <= n+1; ++i) {
            for (int j = 0; j <= m+1; ++j)
                printf("%c", s[i][j]);
            puts("");
        }
        */

        int c0 = 0, c1 = 0;
        for (int i = 0; i <= n + 1; ++i) {
            for (int j = 0; j <= m + 1; ++j) {
                if (vis[i][j]) continue;

                if (s[i][j] == '0') c0++;
                else c1++;
                dfs(i, j, s[i][j]);
            }
        }

        int ans = -1;
        if (c1 == 1) {
            if (c0 == 2)
               ans = 0;
            else if (c0 == 1)
               ans = 1; 
        }
        printf("%d\n", ans);
    }

    return 0;
}

