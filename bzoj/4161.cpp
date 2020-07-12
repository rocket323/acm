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
const int maxl = 5010;
const int mod = 1e9 + 7;

int n, k, a[maxl], c[maxl], t[maxl], h[maxl];
int x[maxl];

void mul(int A[], int B[], int r[]) {
    static int res[maxl << 1];
    memset(res, 0, sizeof(res));

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            res[i + j] = (res[i + j] + (ll)A[i] * B[j]) % mod;
        }
    }

    for (int i = (k << 1) - 2; i >= k; i--) {
        if (!res[i]) continue;
        for (int j = k - 1; j >= 0; j--) {
            res[i - k + j] = (res[i - k + j] + (ll)res[i] * x[j]) % mod;
        }
    }

    for (int i = 0; i < k; i++) r[i] = res[i];
}

int solve(int n, int k) {
    if (n < k) return h[n];
    n = n - k + 1;

    memset(c, 0, sizeof c);
    memset(t, 0, sizeof t);
    c[0] = t[1] = 1;

    while (n) {
        if (n & 1) {
            mul(c, t, c);
        }
        mul(t, t, t);
        n >>= 1;
    }

    return 0;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d", &a[i]);
        if (a[i] < 0) a[i] += mod;
        x[k - i] = a[i];
    }
    memset(h, 0, sizeof h);
    for (int i = 0; i < k; i++) {
        scanf("%d", &h[i]);
        if (h[i] < 0) h[i] += mod;
    }

    for (int i = k; i < k * 2; i++) {
        for (int j = 1; j <= k; j++) {
            h[i] = (h[i] + (ll)a[j] * h[i - j]) % mod;
        }
    }

    solve(n, k);
    int ans = 0;
    for (int i = 0; i < k; i++) {
        ans = (ans + (ll)c[i] * h[k - 1 + i]) % mod;
    }
    printf("%d\n", ans);

    return 0;
}

