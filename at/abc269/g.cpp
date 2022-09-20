#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 7e5 + 10;

int n, m, a[maxl], b[maxl], c[maxl];
int x[maxl], top;
unordered_map<int, int> mp;
int f[2][maxl];

void split(int n, int x[], int &top) {
    top = 0;
    int t = 1;
    while (n > 0) {
        int s = min(t, n);
        x[top++] = s;
        n -= s;
        t <<= 1;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    int sum = 0;
    int B = 2 * m;
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        c[i] = b[i] - a[i];
        mp[c[i]]++;
        sum += a[i];
    }
    memset(f, 0x3f, sizeof f);
    f[0][sum + B] = 0;
    int idx = 0;
    for (auto &&[k, v] : mp) {
        split(v, x, top);
        for (int i = 0; i < top; i++) {
            int t = x[i] * k;
            idx ^= 1;
            memset(f[idx], 0x3f, sizeof(f[idx]));
            for (int j = -m; j <= m; j++) {
                f[idx][j + B] = min(f[idx ^ 1][j + B], f[idx ^ 1][j - t + B] + x[i]);
            }
        }
    }
    for (int i = 0; i <= m; i++) {
        printf("%d\n", f[idx][i + B] >= inf ? -1 : f[idx][i + B]);
    }
    return 0;
}