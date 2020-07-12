#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int n, x, y, d;
int a[maxl], f[maxl], top;

int main() {
    scanf("%d", &n);
    scanf("%d%d", &x, &y);
    d = 0;
    int b;
    top = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &b);
        if (b == 1) continue;
        if (b - 1 > y - x) continue;
        a[top++] = b - 1;
    }

    memset(f, 0, sizeof f);
    int m = y - x;
    f[0] = 1;
    for (int i = 0; i < top; ++i) {
        int x = a[i];
        for (int j = x; j <= m; ++j) {
            if (f[j - x])
                f[j] = 1;
        }
    }
    puts(f[m] ? "POSSIBLE" : "IMPOSSIBLE");

    return 0;
}

