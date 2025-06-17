#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 3e5 + 10;

int n, l;
int d[maxl], C[maxl];

int main() {
    scanf("%d%d", &n, &l);
    C[0] = 1;
    int pos = 0;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d", &d[i]);
        pos = (pos + d[i]) % l;
        C[pos]++;
    }
    ll ans = 0;
    if (l % 3 == 0) {
        int x = l / 3;
        for (int i = 0; i < l; i++) {
            ll a = C[i];
            ll b = C[(i + x) % l];
            ll c = C[(i + x + x) % l];
            ans += a * b * c;
        }
    }
    ans /= 3;
    cout << ans << endl;
    return 0;
}
