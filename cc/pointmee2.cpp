#include <bits/stdc++.h>
using namespace std;

const int maxl = 110;
int t, n;
double x[maxl], y[maxl];

int gao(double x0, double y0) {
    int ret = 0;
    for (int i = 1; i <= n; ++i) {
        if (x[i] == x0 && y[i] == y0)
            continue;
        if ((x[i] == x0) || (y[i] == y0))
            ret++;
        else if (y[i] - x[i] == y0 - x0)
            ret++;
        else if ((x0 - x[i] == y[i] - y0))
            ret++;
        else
            ret += 2;
    }
    return ret;
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> x[i];
        }
        for (int i = 1; i <= n; ++i) {
            cin >> y[i];
        }
        int ans = n * 2;
        for (int i = 1; i <= n; ++i) {
            ans = min(ans, gao(x[i], y[i]));
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                ans = min(ans, gao(x[j], y[i]));
                ans = min(ans, gao(x[j] + y[i] - y[j], y[i]));
                ans = min(ans, gao(x[j] - y[i] + y[j], y[i]));

                ans = min(ans, gao(x[i], y[j]));
                ans = min(ans, gao(x[i], y[j] + x[j] - x[i]));
                ans = min(ans, gao(x[i], y[j] - x[j] + x[i]));

                ans = min(ans, gao(x[j], y[i] + x[j] - x[i]));
                ans = min(ans, gao(x[i] + y[j] - y[i], y[j]));
                ans = min(ans, gao((-y[i] + x[i] + y[j] + x[j]) / 2, (y[i] - x[i] + y[j] + x[j]) / 2));

                ans = min(ans, gao(x[i] - y[j] + y[i], y[j]));
                ans = min(ans, gao(x[j], y[i] - x[j] + x[i]));
                ans = min(ans, gao((-y[j] + x[j] + y[i] + x[i]) / 2, (y[j] - x[j] + y[i] + x[i]) / 2));
            }
        }
        cout << ans << endl;
    }

    return 0;
}
