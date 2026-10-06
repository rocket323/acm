#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e3 + 10;

int n, a[maxl];
ll f[maxl][maxl];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        f[i][i] = 0;
    }
    sort(a, a + n);
    for (int k = 2; k <= n; k++) {
        for (int i = 0; i + k - 1 < n; i++) {
            int j = i + k - 1;
            ll x = min(f[i + 1][j], f[i][j - 1]);
            f[i][j] = x + a[j] - a[i];
        }
    }
    cout << f[0][n - 1] << endl;
    return 0;
}
