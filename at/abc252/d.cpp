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

int n;
ll a[maxl], sa[maxl], b[maxl], sb[maxl], c[maxl], sc[maxl];
int v;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v);
        a[v]++;
    }
    for (int i = maxl - 2; i >= 1; i--) {
        sa[i] = sa[i + 1] + a[i];
    }
    for (int i = maxl - 2; i >= 1; i--) {
        b[i] = a[i] * sa[i + 1];
    }
    for (int i = maxl - 2; i >= 1; i--) {
        sb[i] = sb[i + 1] + b[i];
    }
    ll ans = 0;
    for (int i = maxl - 2; i >= 1; i--) {
        c[i] = a[i] * sb[i + 1];
        ans += c[i];
    }
    cout << ans << endl;
    return 0;
}