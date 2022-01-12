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
using ll = unsigned long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;

ll x;

ll gao(ll x) {
    if (x < 10)
        return x;

    ll ans = (1ull << 63);
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            ll t = i * 10 + j;
            int cur = j;
            int d = j - i;
            while (t < x) {
                cur += d;
                if (cur < 0 || cur > 9)
                    break;
                t = t * 10 + cur;
            }
            if (t >= x && t < ans)
                ans = t;
        }
    }
    return ans;
}

int main() {
    while (cin >> x) {
        ll y = gao(x);
        cout << y << endl;
    }
    return 0;
}
