#include <bits/stdc++.h>
using namespace std;

double eps = 1e-8;
const int maxl = 1e5 + 10;
int n, d, x[maxl], t;
double f[maxl];
bool g[maxl];

bool check(double l) {
    memset(g, 0, sizeof(g));
    for (int i = 0; i <= n; i++)
        f[i] = 0;
    g[0] = 1;
    for (int i = 2; i <= n; i++) {
        if (g[i - 2] && x[i - 1] + l + d >= x[i] - l) {
            g[i] = 1;
            double tmp = std::min(x[i - 1] + l + d, x[i] + l);
            if (tmp > f[i])
                f[i] = tmp;
        }
        if (g[i - 1] && f[i - 1] + d >= x[i] - l) {
            g[i] = 1;
            double tmp = std::min(f[i - 1] + d, x[i] + l);
            if (tmp > f[i])
                f[i] = tmp;
        }
    }

    return g[n];
}

void solve() {
    double l = 0, r = 2e9, ans = 0;
    while (l <= r) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - eps;
        } else {
            l = mid + eps;
        }
    }

    printf("%.8lf\n", ans);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &d);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &x[i]);
        }
        sort(x + 1, x + 1 + n);
        solve();
    }
    return 0;
}
