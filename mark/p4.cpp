#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e5 + 10;
int n, m, f[maxl], c[maxl], v[maxl];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &c[i], &v[i]);
        }
        memset(f, 0, sizeof f);
        for (int i = 1; i <= n; i++) {
            for (int j = m; j >= c[i]; j--) {
                f[j] = max(f[j], f[j - c[i]] + v[i]);
            }
        }
        printf("%d\n", f[m]);
    }
    return 0;
}