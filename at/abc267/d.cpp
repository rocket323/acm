#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2020;

int n, m;
int a[maxl];
ll f[maxl][maxl];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        f[i][0] = 0;
        for (int j = 1; j <= min(i, m); j++) {
            f[i][j] = f[i - 1][j - 1] + (ll)a[i] * j;
            if (i - 1 >= j)
                f[i][j] = max(f[i][j], f[i - 1][j]);
        }
    }
    cout << f[n][m] << endl;
    return 0;
}