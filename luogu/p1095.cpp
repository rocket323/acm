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
const int maxl = 2e5 + 10;

int m, s, t, M;
int f[2][1050];

int main() {
    while (scanf("%d%d%d", &m, &s, &t) != EOF) {
        memset(f, 0x80, sizeof f);
        f[0][m] = 0;
        M = 1010;
        int idx = 1;
        int max_dist = 0;
        int min_time = t + 1;
        for (int i = 1; i <= t; i++) {
            for (int j = 0; j <= M; j++) {
                f[idx][j] = max({f[idx ^ 1][j + 10] + 60, f[idx ^ 1][j] + 17, j >= 4 ? f[idx ^ 1][j - 4] : -inf});
                if (f[idx][j] >= s)
                    min_time = min(min_time, i);
                max_dist = max(max_dist, f[idx][j]);
            }
            idx ^= 1;
        }
        if (max_dist >= s)
            printf("Yes\n%d\n", min_time);
        else
            printf("No\n%d\n", max_dist);
    }
    return 0;
}