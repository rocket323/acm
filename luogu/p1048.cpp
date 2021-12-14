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

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;

int n, m, c[maxl], v[maxl];
int f[maxl];

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &c[i], &v[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= c[i]; j--) {
            f[j] = max(f[j], f[j - c[i]] + v[i]);
        }
    }
    printf("%d\n", f[m]);

    return 0;
}
