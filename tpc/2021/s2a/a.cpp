#include <bits/stdc++.h>

const int maxl = 1010;
int t, n, k, a[maxl], b[maxl], c[maxl];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d", &b[i]);

            c[i] = i == 1 ? a[i] + b[i] : a[i];
        }

        int cnt = 0;
        for (int i = 2; i <= n; i++) {
            if (c[i] > c[1])
                cnt++;
        }

        puts(cnt + 1 <= k ? "Yes" : "No");
    }

    return 0;
}