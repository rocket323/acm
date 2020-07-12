#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int n, m, q, c;
char s[210][210];
int cost[210];
int sum[2][210][210];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", s[i] + 1);

    memset(sum, 0, sizeof sum);
    memset(cost, 0x3f, sizeof cost);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {

            for (int k = 0; k < 2; k++) {
                char target = '0' + ((i + j + k) % 2);
                sum[k][i][j] = (s[i][j] != target);
                // if (k == 0)
                //     printf("%d/%d ", target, s[i][j]);

                sum[k][i][j] += (sum[k][i-1][j] + sum[k][i][j-1]);
                sum[k][i][j] -= sum[k][i-1][j-1];
            }
        }
        // puts("");
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; i + k - 1 <= n && j + k - 1 <= m; k++) {
                for (int c = 0; c < 2; c++) {
                    int v = sum[c][i+k-1][j+k-1] - sum[c][i+k-1][j-1] - sum[c][i-1][j+k-1] + sum[c][i-1][j-1];
                    cost[k] = min(cost[k], v);
                }
            }
        }
    }
    for (int k = min(n, m); k >= 1; k--) {
        cost[k] = min(cost[k+1], cost[k]);
        // printf("%d %d\n", k, cost[k]);
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &c);

        int l = 1, r = min(n, m), ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (cost[mid] <= c) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}

