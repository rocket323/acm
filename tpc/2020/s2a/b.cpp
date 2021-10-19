#include <bits/stdc++.h>

const int maxl = 1e5 + 10;
typedef long long ll;

using namespace std;

int t;
int n, m, a[maxl];
ll b[maxl];

int get(int x) {
    if (x == -1)
        return 0;
    return x;
}

ll solve() {
    b[1] = get(a[1]);
    b[2] = get(a[2]);
    for (int i = 3; i <= n; i++) {
        b[i] = get(a[i]);

        int idx = -1;
        ll sum = (ll)b[i] + b[i - 1] + b[i - 2];
        for (int j = i; j >= i - 2; j--) {
            if (a[j] == -1) {
                idx = j;
                break;
            }
        }

        if (sum < m) {
            if (idx == -1)
                return -1;

            b[idx] += (m - sum);
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++)
        ans += b[i];

    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }

        ll ans = solve();
        if (ans == -1)
            puts("Impossible");
        else
            cout << ans << endl;
    }

    return 0;
}
