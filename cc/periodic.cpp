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

int t, n, a[maxl];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        bool all_neg = true;
        int idx = -1;
        int mx = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            mx = max(mx, a[i]);
            if (a[i] != -1) {
                all_neg = false;
                if (idx == -1)
                    idx = i;
            }
        }

        if (all_neg) {
            puts("inf");
            continue;
        }

        int ans = -1;
        for (int i = mx + n + 20; i >= mx; i--) {
            bool ok = true;
            for (int j = 0; j < n; j++) {
                if (a[j] != -1 && a[j] != (a[idx] - 1 + j - idx) % i + 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ans = i;
                break;
            }
        }
        if (ans == -1)
            puts("impossible");
        else if (ans >= mx + n + 20)
            puts("inf");
        else
            printf("%d\n", ans);
    }

    return 0;
}

