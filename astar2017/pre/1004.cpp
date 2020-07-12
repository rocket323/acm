#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define maxl 105

int n, m, v[maxl], c[maxl];
int f[105][1010], g[105][1010], t;

void solve() {
    memset(f, 0, sizeof f);
    memset(g, 0, sizeof g);
    
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= 0; --j) {
            f[i][j] = f[i - 1][j];
            if (j >= c[i]) {
                if (f[i - 1][j - c[i]] + v[i] > f[i][j]) {
                    f[i][j] = max(f[i][j], f[i - 1][j - c[i]] + v[i]);
                    g[i][j] = true;
                }
            }
        }
    }

    std::vector<int> vec;
    int j = m, ans = 0;
    for (int i = n; i >= 1; --i) {
        if (g[i][j]) {
            vec.push_back(i);
            ans += c[i];
            j -= c[i];
        }
    }
    reverse(vec.begin(), vec.end());
    
    printf("%d %d\n", f[n][m], ans);
    for (size_t i = 0; i < vec.size(); ++i) {
        printf("%d%c", vec[i], (i == vec.size() - 1) ? '\n' : ' ');
    }
}

int main() {
    scanf("%d", &t);
    for (int x = 1; x <= t; ++x) {
        scanf("%d%d", &m, &n);
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &v[i], &c[i]);

        printf("Case #%d:\n", x);
        solve();
    }

    return 0;
}

