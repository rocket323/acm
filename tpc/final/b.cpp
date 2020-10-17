#include <stdio.h>
#include <cstring>
#include <queue>

using namespace std;

const int maxl = (1 << 17) + 10;
int t;
bool vis[maxl];
char a[4][4], b[4][4];

bool check(char a[][4]) {
    int lines = 0;
    for (int i = 0; i < 4; i++) {
        int x = 0;
        for (int j = 0; j < 4; j++) {
            if (a[i][j] == '#')
                x++;
        }
        if (x == 4)
            lines++;
    }

    for (int j = 0; j < 4; j++) {
        int x = 0;
        for (int i = 0; i < 4; i++) {
            if (a[i][j] == '#')
                x++;
        }
        if (x == 4)
            lines++;
    }

    int x = 0;
    for (int i = 0; i < 4; i++) {
        if (a[i][i] == '#')
            x++;
    }
    if (x == 4)
        lines++;

    x = 0;
    for (int i = 0; i < 4; i++) {
        if (a[i][3 - i] == '#')
            x++;
    }
    if (x == 4)
        lines++;

    return lines >= 3;
}

int calc(char a[][4]) {
    int x = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int y = (a[i][j] == '#') ? 1 : 0;
            x = x * 2 + y;
        }
    }
    return x;
}

void paint(int n) {
    if (n <= 4) {
        for (int i = 0; i < 4; i++)
            b[n - 1][i] = '#';
    } else if (n <= 8) {
        for (int i = 0; i < 4; i++)
            b[i][n - 4 - 1] = '#';
    } else if (n == 9) {
        for (int i = 0; i < 4; i++)
            b[i][i] = '#';
    } else {
        for (int i = 0; i < 4; i++)
            b[i][3 - i] = '#';
    }
}

int check() {
    int num = 0;
    int ans = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (b[i][j] == '#') {
                num++;
                if (a[i][j] != '#')
                    ans++;
            }
        }
    }
    if (num != 9)
        return 10000;
    return ans;
}

void solve() {
    int ans = 10000;

    for (int x = 0; x < 4; x++)
        for (int y = 0; y < 4; y++)
            b[x][y] = '.';
    for (int i = 1; i <= 10; i++) {
        for (int j = i; j <= 10; j++) {
            for (int k = j; k <= 10; k++) {
                paint(i);
                paint(j);
                paint(k);

                ans = min(ans, check());

                for (int x = 0; x < 4; x++)
                    for (int y = 0; y < 4; y++)
                        b[x][y] = '.';
            }
        }
    }
    printf("%d\n", ans);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(vis, 0, sizeof vis);
        for (int i = 0; i < 4; i++) {
            scanf("%s", a[i]);
        }

        solve();
    }
    return 0;
}
