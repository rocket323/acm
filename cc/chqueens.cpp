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
const int maxl = 105;
const int mod = 1e9 + 7;

int t, n, m, x, y;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d%d", &n, &m, &x, &y);
        int ans = 0;

        int c1 = min(x - 1, y - 1);
        int c2 = min(n - x, m - y);

        ans += c1 * (c1 - 1) + c2 * (c2 - 1);

        int t1 = min(n - x, y - 1);
        int t2 = min(x - 1, m - y);

        ans += t1 * (t1 - 1) + t2 * (t2 - 1);

        int p1 = y - 1, p2 = m - y;
        ans += p1 * (p1 - 1) + p2 * (p2 - 1);

        int q1 = x - 1, q2 = n - x;
        ans += q1 * (q1 - 1) + q2 * (q2 - 1);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (i != x) ans += (m - 1);
                if (j != y) ans += (n - 1);
                if (i - j != x - y) {
                    int l = min(i - 1, j - 1) + min(n - i, m - j);
                    ans += l;
                }
                if (i + j != x + y) {
                    int l = min(n - i, j - 1) + min(i - 1, m - j);
                    ans += l;
                }
            }
        }
        ans = (n * m - 1) * (n * m - 2) - ans;
        printf("%d\n", ans);
    }

    return 0;
}

