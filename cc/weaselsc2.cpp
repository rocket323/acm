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

int t, n, k, a[maxl];
int g[maxl][20];
ll f[55][maxl];
int L[maxl], R[maxl];
int st[maxl], top, curHeight;

double slope(int x, int k, int j) {
    double xx = (double)a[k] * (k + 1) - (double)a[j] * (j + 1);
    xx += f[x][j] - f[x][k];
    double y = a[k] - a[j];
    return xx / y;
}

void add(int x, int p) {
    if (f[x][p] == 0) {
        if (a[p] <= curHeight)
            top = 0;
        curHeight = a[p];
        return;
    }

    if (top == 0) {
        st[top++] = p;
        curHeight = a[p];
        return;
    }
    else {
        if (curHeight >= a[p])
            top = 0;

        while (top >= 2) {
            double s1 = slope(x, st[top - 2], st[top - 1]);
            double s2 = slope(x, st[top - 1], p);
            if (s1 <= s2)
                top--;
            else
                break;
        }
        st[top++] = p;
        curHeight = a[p];
    }
}

ll solve() {
    for (int i = 1; i <= n; ++i) {
        L[i] = i;
        R[i] = i;
        while (i > 1 && a[L[i] - 1] >= a[i]) L[i]--;
        while (i < n && a[R[i] + 1] >= a[i]) R[i]++;
    }
    memset(f, 0, sizeof f);

    ll ans = 0;
    for (int x = 1; x <= k + 1; ++x) {
        int last = 0;
        top = 0;
        curHeight = 0;
        for (int i = 1; i <= n; ++i) {
            ll t2 = (ll)a[i] * (i - L[i] + 1);

            while (last + 1 < i) {
                add(x - 1, last + 1);
                last++;
            }

            int l = 0, r = top - 1, p = -1;
            int idx = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (a[mid] < a[i]) {
                    idx = mid;
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }

            ll t1 = 0;
            if (idx != -1) {
                p = st[idx];
                l = 0, r = idx - 1;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    double s = slope(x - 1, st[mid], st[mid + 1]);
                    if (s <= L[i]) {
                        p = st[mid];
                        r = mid - 1;
                    }
                    else
                        l = mid + 1;
                }

                t1 = (ll)a[p] * (L[i] - p - 1) + f[x - 1][p];
            }
            f[x][i] = t1 + t2;
            printf("%d %d p %d, %lld %lld\n", x, i, p, t1, t2);

            ll tmp = f[x][i] + (ll)a[i] * (R[i] - i);
            ans = max(ans, tmp);
        }
    }
    puts("");
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        memset(a, 0, sizeof a);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);

        ll ans = 0;
        ans = max(ans, solve());
        reverse(a + 1, a + 1 + n);
        ans = max(ans, solve());

        printf("%lld\n", ans);
    }

    return 0;
}

