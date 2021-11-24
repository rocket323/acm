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
const int maxl = 3030;

int t, a[maxl], n;

ll gao(int i, int j, int k) {
    return (ll)(a[i] - a[j]) * (ll)(a[j] - a[k]);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            int p = i + 1;
            for (int j = i+2; j <= n; j++) {
                while (p + 1 < j && gao(i, p, j) <= gao(i, p + 1, j))
                    p++;
                ans += gao(i, p, j);
            }
        }
        cout << ans << endl;
    }
    return 0;
}

