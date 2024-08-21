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
const int maxl = 500 + 10;

int n;
char s[maxl];
int f[maxl][maxl];

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);

    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
        f[i][i] = 1;

    for (int k = 2; k <= n; k++) {
        for (int i = 1; i + k - 1 <= n; i++) {
            int j = i + k - 1;
            f[i][j] = 1 + f[i + 1][j];
            for (int x = i + 1; x <= j; x++) {
                if (s[x] != s[i])
                    continue;
                int t = i + 1 > x - 1 ? 0 : f[i + 1][x - 1];
                f[i][j] = min(f[i][j], t + f[x][j]);
            }
        }
    }
    printf("%d\n", f[1][n]);
    return 0;
}