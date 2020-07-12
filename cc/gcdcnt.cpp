#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int n, m, a[maxl];
int op, BS;
int p[maxl], top, f[maxl];
short c[260][maxl];

int cnt[maxl];
vector<int> fac[maxl];

int factor(int n) {
    int c = 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            c++;
            if (n / i % i == 0)
                return -1;
            n /= i;
        }
    }
    if (n > 1)
        c++;
    return c;
}

void init() {
    memset(cnt, -1, sizeof cnt);
    for (int i = 2; i < maxl; i++)
        cnt[i] = factor(i);

    for (int i = 1; i < maxl; i++) {
        for (int j = 1; j * j <= i; j++) {
            if (i % j) continue;
            if (cnt[j] != -1) fac[i].push_back(j);
            int k = i / j;
            if (k != j && cnt[k] != -1) fac[i].push_back(k);
        }
        sort(fac[i].begin(), fac[i].end());
    }
}

void add(int p, int n, int v) {
    int b = p / BS;
    for (int f : fac[n]) {
        c[b][f] += v;
    }
}

int get(int r, int g) {
    if (r == -1) return 0;

    int b = r / BS;
    int ans = 0;
    for (int i = 0; i < b; i++) {
        for (int j = 0; j < fac[g].size(); j++) {
            int f = fac[g][j];
            int sign = cnt[f];
            if (sign & 1)
                ans += c[i][f];
            else
                ans -= c[i][f];
        }
    }

    for (int i = b * BS; i <= r; i++) {
        for (int j = 0; j < fac[g].size(); j++) {
            int f = fac[g][j];
            if (a[i] % f) continue;
            int sign = cnt[f];
            if (sign & 1)
                ans++;
            else
                ans--;
        }
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    BS = sqrt(n) + 10;

    init();

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        add(i, a[i], 1);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            scanf("%d%d", &x, &y);
            x--;
            add(x, a[x], -1);
            add(x, y, 1);
            a[x] = y;
        } else {
            int l, r, g;
            scanf("%d%d%d", &l, &r, &g);
            l--;
            r--;
            int ans = get(r, g) - get(l - 1, g);
            printf("%d\n", (r - l + 1) - ans);
        }
    }

    return 0;
}

