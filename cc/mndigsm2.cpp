#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e13;
const ll X = 20000;
ll t, n, r, ans;
ll k;

ll gao(ll k) {
    ll ans = 0;
    ll x = n;
    while (x) {
        ans += x % k;
        x /= k;
    }
    return ans;
}

void update(ll tmp, ll base) {
    if (tmp < ans) {
        ans = tmp;
        k = base;
    }
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> r;

        ans = inf;
        k = 0;
        for (ll i = 2; i <= r && i <= X; i++) {
            ll tmp = gao(i);
            update(tmp, i);
        }

        for (ll a = 0; a <= 40; a++) {
            for (ll b = 0; b <= 40; b++) {
                ll left = X + 1, right = r;
                ll kk = -1, pp = 0;
                while (left <= right) {
                    ll mid = (left + right) / 2;
                    if (a * mid + b <= n / mid) {
                        ll sum = a * mid * mid + b * mid;
                        if (n - sum < mid) {
                            kk = mid;
                            pp = a + b + (n - sum);
                        }
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }
                if (kk != -1) {
                    update(pp, kk);
                }
            }
        }

        cout << k << endl;
    }

    return 0;
}
