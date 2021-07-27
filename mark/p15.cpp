#include <bits/stdc++.h>

int a[20], n, m, t;
int ans;

void dfs(int i, int s) {
    if (i == n) {
        ans += (s % m == 0);
        return;
    }

    dfs(i + 1, s);
    dfs(i + 1, s + a[i]);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        ans = 0;
        dfs(0, 0);
        printf("%d\n", ans - 1);
    }

    return 0;
}
