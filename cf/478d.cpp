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
const int maxl = 4e5 + 10;
const int mod = 1e9 + 7;

int r, g, f[maxl], sq = 650;

void gao() {
    int h = 0, sum = 0;
    while (sum + (h + 1) <= r + g) {
        h++;
        sum += h;
    }
    memset(f, 0, sizeof f);
    f[0] = 1;
    for (int i = 1; i <= h; i++) {
        for (int j = sum; j >= i; j--) {
            f[j] = (f[j] + f[j - i]) % mod;
        }
    }

    int ans = 0;
    for (int i = max(0, sum - r); i <= g; i++) {
        ans = (ans + f[i]) % mod;
    }
    printf("%d\n", ans);
}

int main() {
    while (scanf("%d%d", &r, &g) != EOF) {
        gao();
    }
    return 0;
}