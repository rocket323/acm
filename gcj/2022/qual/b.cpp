#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e5 + 10;

int t, a[10][10], ans[10], mn[10];

int main() {
    scanf("%d", &t);
    for (int tc = 1; tc <= t; tc++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++)
                scanf("%d", &a[i][j]);
        }
        int m = 1e6;
        for (int j = 0; j < 4; j++) {
            mn[j] = 0x3f3f3f3f;
            for (int i = 0; i < 3; i++)
                mn[j] = min(mn[j], a[i][j]);
            if (mn[j] >= m) {
                ans[j] = m;
                m = 0;
            } else {
                m -= mn[j];
                ans[j] = mn[j];
            }
        }
        printf("Case #%d: ", tc);
        if (m > 0) {
            puts("IMPOSSIBLE");
        } else {
            for (int j = 0; j < 4; j++) {
                printf("%d%c", ans[j], (j == 3) ? '\n' : ' ');
            }
        }
    }
    return 0;
}