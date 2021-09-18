#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;
int a[10][10], l[10], r[10], b[10][10];
int ans, n, vis[10][10];
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

void dfs(int r, int c, int ch) {
    vis[r][c] = 1;
    for (int k = 0; k < 4; k++) {
        int rr = r + dr[k];
        int cc = c + dc[k];
        if (rr >= 0 && rr <= 5 && cc >= 0 && cc <= 5) {
            if (!vis[rr][cc] && b[rr][cc] == ch) {
                dfs(rr, cc, ch);
            }
        }
    }
}

int calc(int ch) {
    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            vis[i][j] = 0;
        }
    }
    int cnt = 0;
    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            if (b[i][j] == ch && !vis[i][j]) {
                cnt++;
                dfs(i, j, ch);
            }
        }
    }
    return cnt;
}

bool check(int s) {
    for (int i = 0; i <= 5; i++)
        for (int j = 0; j <= 5; j++)
            b[i][j] = 0;

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            int x = (i - 1) * 4 + j - 1;
            b[i][j] = ((s & (1 << x)) > 0);

            if (a[i][j] == 1 && b[i][j] == 0)
                return false;
        }
    } 

    return (calc(0) <= 1 && calc(1) == 1);
}

int main() {
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int ans = 0;
    for (int s = 0; s < (1 << 16); s++) {
        if (check(s)) {
            ans++;
        }
    }
    printf("%d\n", ans);

    return 0;
}
