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
const int maxl = 1010;

int n, a[maxl][maxl], c[2][maxl][maxl];
int f[2][maxl][maxl], p[2][maxl][maxl], r1, c1;

int calc(int n, int i) {
    int ans = 0;
    if (n == 0)
        return 0;
    while (n % i == 0) {
        ans++;
        n /= i;
    }
    return ans;
}

void dp(int idx) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            f[idx][i][j] = inf;
        }
    }
    f[idx][1][1] = c[idx][1][1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == 1 && j == 1)
                continue;
            if (f[idx][i - 1][j] < f[idx][i][j - 1]) {
                f[idx][i][j] = f[idx][i - 1][j] + c[idx][i][j];
                p[idx][i][j] = 0;
            } else {
                f[idx][i][j] = f[idx][i][j - 1] + c[idx][i][j];
                p[idx][i][j] = 1;
            }
        }
    }
}

int solve() {
    dp(0);
    dp(1);
    int idx = f[0][n][n] < f[1][n][n] ? 0 : 1;
    return f[idx][n][n];
}

void output() {
    int idx = f[0][n][n] < f[1][n][n] ? 0 : 1;
    std::vector<char> v;
    int i = n, j = n;
    while (!(i == 1 && j == 1)) {
        if (p[idx][i][j] == 0) {
            v.push_back('D');
            i = i - 1;
        } else {
            v.push_back('R');
            j = j - 1;
        }
    }
    for (int i = v.size() - 1; i >= 0; i--) {
        printf("%c", v[i]);
    }
    puts("");
}

void solve1() {
    int x = solve();
    printf("%d\n", x);
    output();
}

void solve2() {
    int x = solve();
    if (x == 0) {
        printf("%d\n", x);
        output();
        return;
    }

    printf("1\n");
    for (int i = 1; i < r1; i++)
        printf("D");
    for (int j = 1; j < n; j++)
        printf("R");
    for (int j = r1 + 1; j <= n; j++)
        printf("D");
    puts("");
}

int main() {
    scanf("%d", &n);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 0) {
                cnt++;
                a[i][j] = 10;
                r1 = i;
                c1 = j;
            }
            c[0][i][j] = calc(a[i][j], 2);
            c[1][i][j] = calc(a[i][j], 5);
        }
    }
    if (cnt == 0)
        solve1();
    else
        solve2();
    return 0;
}