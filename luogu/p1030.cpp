#include <assert.h>
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

char s[maxl], t[maxl];
int n, c[maxl][2];

int dfs(int l, int r, int l2, int r2) {
    if (l > r)
        return -1;

    int m = -1;
    for (int i = l; i <= r; i++) {
        if (s[i] == t[r2]) {
            m = i;
            break;
        }
    }
    assert(m >= 0);
    int d = m - l;

    int root = r2;
    c[root][0] = dfs(l, m - 1, l2, l2 + d - 1);
    c[root][1] = dfs(m + 1, r, l2 + d, r2 - 1);
    return root;
}

void out(int u) {
    if (u == -1)
        return;
    printf("%c", t[u]);
    out(c[u][0]);
    out(c[u][1]);
}

int main() {
    scanf("%s%s", s, t);
    n = strlen(s);
    int x = dfs(0, n - 1, 0, n - 1);
    out(x);
    puts("");
    return 0;
}
