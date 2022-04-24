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

const ll inf = 1e16;
const int maxl = 2e5 + 10;

int t, n, p;
ll ans;
int x[1010][105], f[202];
ll a[1010][10], b[1010][10], c[1010][10];

void dfs(int now, ll last, ll sum) {
    if (now == n + 1) {
        if (sum < ans) {
            ans = sum;
        }
        return;
    }

    for (int k = 0; k < f[p]; k++) {
        ll tmp = sum + abs(a[now][k] - last) + b[now][k];
        dfs(now + 1, c[now][k], tmp);
    }
}

ll solve1() {
    ans = inf;
    for (int i = 1; i <= n; i++) {
        int q[5] = {0};
        for (int j = 0; j < p; j++)
            q[j] = j;
        for (int k = 0; k < f[p]; k++) {
            a[i][k] = x[i][q[0]];
            c[i][k] = x[i][q[p - 1]];
            b[i][k] = 0;
            for (int j = 1; j < p; j++) {
                b[i][k] += abs(x[i][q[j]] - x[i][q[j - 1]]);
            }
            next_permutation(q, q + p);
        }
    }

    dfs(1, 0, 0);
    return ans;
}

int main() {
    scanf("%d", &t);
    f[0] = 1;
    f[1] = 1;
    f[2] = 2;
    f[3] = 6;
    for (int tc = 1; tc <= t; tc++) {
        scanf("%d%d", &n, &p);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < p; j++) {
                scanf("%d", &x[i][j]);
            }
        }
        if (n <= 10 && p <= 3) {
            cout << "Case #" << tc << ": " << solve1() << endl;
        }
    }

    return 0;
}