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

int n, k, h[maxl], a[maxl];

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d", &a[i]);
    }

    memset(h, 0, sizeof(h));
    for (int i = 0; i < k; i++) {
        scanf("%d", &h[i]);
    }

    int ans = 0;
    if (n < k) {
        ans = h[n];
    } else {
        for (int i = k; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                h[i] = (h[i] + (ll)a[j] * h[i - j]) % mod;
            }
        }
        ans = h[n];
    }
    printf("%d\n", ans);

    return 0;
}

