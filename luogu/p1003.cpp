#include <bits/stdc++.h>

const int maxl = 100010;

struct rect {
    int x, y, xl, yl;
} r[maxl];

int n, x, y;

bool isIn(int x, int y, int i) {
    int x1 = r[i].x, x2 = r[i].x + r[i].xl - 1;
    int y1 = r[i].y, y2 = r[i].y + r[i].yl - 1;
    return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d%d%d%d", &r[i].x, &r[i].y, &r[i].xl, &r[i].yl);
        }

        scanf("%d%d", &x, &y);

        int ans = -1;
        for (int i = n-1; i >= 0; i--) {
            if (isIn(x, y, i)) {
                ans = i + 1;
                break;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
