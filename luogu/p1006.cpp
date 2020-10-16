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

int n, m, a[100][100], f[60][60][60][60];

void update(int &a, int b) {
    if (b > a)
        a = b;
}

int main() {
    scanf("%d%d", &n, &m);
        assert(n > 1 && m > 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                scanf("%d", &a[i][j]);
        }

        int ans = 0;
        memset(f, -1, sizeof f);
        f[0][0][0][0] = a[0][0];
        for (int i = 0; i < n; i++) {
            for (int l = 0; l < m; l++) {
                for (int r = l; r < m; r++) {
                    for (int s = 0; s <= r; s++) {
                        if (f[i][l][r][s] < 0)
                            continue;

                        int v = f[i][l][r][s];
                        if (i == n - 1 && l == m - 1 && r == m - 1)
                            ans = max(ans, v);

                        if (l + 1 < s || (i == n - 1 && s == m - 1))
                            update(f[i][l+1][r][s], v + a[i][l+1]);

                        update(f[i][l][r+1][s], v + a[i][r+1]);
                        if (l != r)
                            update(f[i+1][l][r][r], v + a[i+1][l] + a[i+1][r]);
                    }
                }
            }
        }

        printf("%d\n", ans);

    return 0;
}
