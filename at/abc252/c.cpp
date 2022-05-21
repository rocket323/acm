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

int n, c[20];
char s[105][20];

int gao(int x) {
    memset(c, -1, sizeof c);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int idx = -1;
        for (int j = 0; j < 10; j++) {
            if (s[i][j] - '0' == x) {
                idx = j;
                break;
            }
        }
        if (c[idx] == -1)
            c[idx] = idx;
        else
            c[idx] += 10;
    }
    for (int i = 0; i < 10; i++)
        ans = max(ans, c[i]);
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
    }
    int ans = inf;
    for (int i = 0; i < 10; i++) {
        int x = gao(i);
        ans = min(ans, x);
    }
    printf("%d\n", ans);
    return 0;
}