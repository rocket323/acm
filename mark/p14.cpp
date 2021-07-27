#include <bits/stdc++.h>
using namespace std;

int n, m, a[10010], b[10010], f[10010];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= a[i]; j--) {
            f[j] = max(f[j], f[j - a[i]] + b[i]);
        }
    }
    printf("%d\n", f[m]);

    return 0;
}
