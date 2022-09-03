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

int n, m;
int a[maxl];
ll s[maxl];
ll ans;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    scanf("%d%d", &n, &m);
    s[0] = 0;
    ll now = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
        if (i <= m)
            now += (ll)i * a[i];
    }

    ans = now;
    for (int i = m + 1; i <= n; i++) {
        now -= (s[i - 1] - s[i - 1 - m]);
        now += (ll)m * a[i];
        if (now > ans)
            ans = now;
    }
    cout << ans << endl;

    return 0;
}