#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const ll inf = 1e18 + 10;
const int maxl = 105;

ll x;
ll c[maxl], n, a[maxl], d[maxl];
ll f[maxl][2];

int main() {
    cin >> n >> x;
    for (int i = n; i >= 1; i--) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        d[i] = x / a[i];
        x %= a[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 2; j++) {
            if (i == 1) {
                f[i][j] = d[i] + j;
            } else {
                ll k = a[i-1] / a[i];
                f[i][j] = d[i] + j + f[i-1][0];
                f[i][j] = min(f[i][j], k - d[i] - j + f[i-1][1]);
            }
        }
    }
    cout << f[n][0] << endl;
    return 0;
}

