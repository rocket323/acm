#include <bits/stdc++.h>

int n, k, a[30], ans;

bool check(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

void dfs(int d, int cnt, int sum) {
    if (d == n) {
        if (cnt == k && check(sum))
            ans++;
        return;
    }

    dfs(d + 1, cnt, sum);
    dfs(d + 1, cnt + 1, sum + a[d]);
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    ans = 0;
    dfs(0, 0, 0);
    printf("%d\n", ans);

    return 0;
}
