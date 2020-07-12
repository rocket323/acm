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
const int inf = 0x3f3f3f3f;

int t, n, k, a[maxl];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        for (int i = 0; i < n; ++i)
            scanf("%d", &a[i]);

        sort(a, a + n);
        n = unique(a, a + n) - a;
        a[n++] = inf;

        int ans = 0, last = -1;
        for (int i = 0; i < n; ++i) {
            if (k >= a[i] - last - 1) {
                k -= a[i] - last - 1;
            } else {
                ans = last + k + 1;
                k = 0;
                break;
            }
            last = a[i];
        }

        printf("%d\n", ans);
    }

    return 0;
}

