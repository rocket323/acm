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
const int maxl = 3e4 + 10;

int n, x, y, f[2][maxl];
vector<int> a, b;

bool check(vector<int> &a, int x, bool tt) {
    int m = a.size();
    int C = 10010, p = 10000;
    int idx = 0;
    memset(f, 0, sizeof f);
    f[idx][C] = 1;
    for (int i = 0; i < m; i++) {
        memset(f[idx ^ 1], 0, sizeof(f[idx ^ 1]));
        for (int j = -p; j <= p; j++) {
            if (!f[idx][j + C])
                continue;
            f[idx ^ 1][j + a[i] + C] = 1;
            if (i > 0 || !tt)
                f[idx ^ 1][j - a[i] + C] = 1;
        }
        idx ^= 1;
    }
    return f[idx][x + C];
}

int main() {
    scanf("%d%d%d", &n, &x, &y);
    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        if (i % 2 == 0)
            a.push_back(v);
        else
            b.push_back(v);
    }
    bool ch = check(a, x, 1) && check(b, y, 0);
    puts(ch ? "Yes" : "No");
    return 0;
}