#include <stdio.h>
#include <cstring>
#include <vector>
using namespace std;
#define maxl 105

int n, m, val[maxl], cost[maxl];
int f[1010], p[1010], t;

int main() {
    scanf("%d", &t);
    for (int x = 1; x <= t; ++x) {
        scanf("%d%d", &m, &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &val[i], &cost[i]);

        memset(f, -1, sizeof f);
        memset(p, -1, sizeof p);
        f[0] = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = m; j >= cost[i]; --j) {
                if (f[j-cost[i]] == -1) continue;

                int tmp = f[j-cost[i]] + val[i];
                if (tmp > f[j]) {
                    f[j] = tmp;
                    p[j] = i;
                }
            }
        }
        int ans = -1, c = -1, idx = -1;
        for (int i = 0; i <= m; ++i) {
            if (f[i] > ans) {
                ans = f[i];
                c = idx = i;
            }
        }
        std::vector<int> v;
        while (p[c] != -1) {
            v.push_back(p[c]);
            printf("xx c:%d, pc:%d, cost:%d\n", c,  p[c], cost[p[c]]);
            c -= cost[p[c]];
        }
        printf("Case #%d:\n", x);
        printf("%d %d\n", ans, idx);
        if (v.size() > 0) {
            for (int i = v.size() - 1; i >= 0; --i) {
                printf("%d%c", v[i], (i == 0) ? '\n' : ' ');
            }
        }
    }

    return 0;
}

