#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;
using ll = unsigned long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;
const int mod = 1e9 + 7;

unsigned n, x, l[maxl];
unordered_set<ll> c[maxl];

int main() {
    scanf("%u", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%u", &l[i]);

        ll num = 0;
        for (int j = 0; j < l[i]; j++) {
            scanf("%u", &x);
            num = (ll)num * mod + x;
        }
        c[l[i]].insert(num);
    }

    int ans = 0;
    for (int i = 0; i < maxl; i++) {
        ans += c[i].size();
    }
    cout << ans << endl;

    return 0;
}

