#include <stdio.h>
#include <cstring>
#include <algorithm>

const int maxl = 3e5 + 10;
int t, n, a[maxl];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int op = 0, ep = 0;
        int ov = 0, ev = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            if (i & 1)
                op++;
            else
                ep++;
            if (a[i] & 1)
                ov++;
            else
                ev++;
        }
        int ans = std::min(op, ev) + std::min(ep, ov);
        printf("%d\n", ans);
    }

    return 0;
}

