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
const int maxl = 2e5 + 10;

int n, a[maxl], b[maxl], m;
char s[maxl];
ll k, sum[maxl];

ll getSum(int i, int j) {
    ll ans = sum[j];
    if (i > 0)
        ans -= sum[i - 1];
    return ans;
}

bool check(int l) {
    for (int i = 0; i + l - 1 < m; i++) {
        int j = i + l - 1;
        int mid = (i + j) / 2;
        ll s1 = (ll)b[mid] * (mid - i + 1) - getSum(i, mid);
        ll s2 = getSum(mid, j) - (ll)b[mid] * (j - mid + 1);
        if (s1 + s2 <= k)
            return true;
    }
    return false;
}

int main() {
    scanf("%s", s);
    scanf("%lld", &k);
    n = strlen(s);
    m = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'Y') {
            a[m++] = i;
        }
    }

    for (int i = 0; i < m; i++) {
        b[i] = a[i] - i;
        sum[i] = b[i] + (i > 0 ? sum[i - 1] : 0);
    }

    int l = 1, r = m, ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    printf("%d\n", ans);

    return 0;
}
