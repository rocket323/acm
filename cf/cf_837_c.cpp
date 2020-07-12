#include <stdio.h>
#include <cstring>
#include <algorithm>

using namespace std;

int n, a, b, x[200], y[200];

bool check(int x1, int y1, int x2, int y2) {
    int x = x1 + x2, y = y1 + y2;

    if (x <= a && max(y1, y2) <= b) return true;
    if (x <= b && max(y1, y2) <= a) return true;
    if (y <= a && max(x1, x2) <= b) return true;
    if (y <= b && max(x1, x2) <= a) return true;
    return false;
}

int main() {
    while (scanf("%d%d%d", &n, &a, &b) != EOF) {
        for (int i = 0; i < n; ++i)
            scanf("%d%d", &x[i], &y[i]);

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                bool fit = false;
                fit |= check(x[i], y[i], x[j], y[j]);
                fit |= check(y[i], x[i], x[j], y[j]);

                fit |= check(x[i], y[i], y[j], x[j]);
                fit |= check(y[i], x[i], y[j], x[j]);

                if (fit) {
                    ans = max(ans, x[i] * y[i] + x[j] * y[j]);
                }
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}

