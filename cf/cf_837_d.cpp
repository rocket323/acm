#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define maxl 205

int n, k, c5[maxl], c2[maxl];
ll a[maxl];
short f[2][maxl][5300];
int sum5[maxl];

int main() {

    while (scanf("%d%d", &n, &k) != EOF) {
        memset(c2, 0, sizeof c2);
        memset(c5, 0, sizeof c5);
        memset(sum5, 0, sizeof sum5);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];

            ll num = a[i];
            while (num % 5 == 0) {
                c5[i]++;
                num /= 5;
            }
            num = a[i];
            while (num % 2 == 0) {
                c2[i]++;
                num /= 2;
            }
            sum5[i] = sum5[i-1] + c5[i];
        }

        int ans = 0;
        memset(f, -1, sizeof f);
        f[0][0][0] = 0;
        int idx = 0;
        for (int i = 0; i <= n; ++i) {
            memset(f[idx^1], -1, sizeof f[idx^1]);
            for (int j = 0; j <= k; ++j) {
                for (int x = 0; x <= sum5[i]; ++x) {
                    if (f[idx][j][x] == -1) continue;
                    if (j == k) ans = max(ans, min(x, (int)f[idx][j][x]));

                    int x2 = c2[i+1], x5 = c5[i+1];
                    f[idx^1][j][x] = max((int)f[idx^1][j][x], (int)f[idx][j][x]);
                    f[idx^1][j+1][x+x5] = max((int)f[idx^1][j+1][x+x5], (int)f[idx][j][x] + x2);
                }
            }
            idx ^= 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}

