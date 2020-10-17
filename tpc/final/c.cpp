#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
using ll = long long;

const int maxl = 1010;
int t;
int n, m, a[maxl], b[maxl];

int gcd(int a, int b) {
    if (a < b)
        swap(a, b);
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

bool check() {
    for (int i = 1; i <= n; i++) {
        bool succ = false;
        for (int j = 1; j <= m; j++) {
            ll x = b[j] / gcd(a[i], b[j]);
            if (x == 1) {
                succ = true;
                break;
            }
        }
        if (!succ)
            return false;
    }

    for (int i = 1; i <= m; i++) {
        bool succ = false;
        for (int j = 1; j <= n; j++) {
            ll x = a[j] / gcd(a[j], b[i]);
            if (x == 1) {
                succ = true;
                break;
            }
        }
        if (!succ)
            return false;
    }

    return true;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);

        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);

        for (int i = 1; i <= m; i++)
            scanf("%d", &b[i]);

        if (!check()) {
            puts("No");
        } else {
            puts("Yes");
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    ll ans = (ll)a[i] * b[j] / gcd(a[i], b[j]);
                    printf("%lld%c", ans, (j == m) ? '\n' : ' ');
                }
            }
        }
    }
    return 0;
}
