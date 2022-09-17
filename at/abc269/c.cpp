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
const int maxl = 2e6 + 10;

ll n;
ll x[100], m;
ll b[maxl], top;

void init(ll n) {
    ll t = 1;
    while (n) {
        if (n & 1) {
            x[m++] = t;
        }
        t <<= 1;
        n >>= 1;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    cin >> n;
    init(n);

    top = 0;
    for (ll st = 0; st < (1 << m); st++) {
        ll tmp = 0;
        for (int i = 0; i < m; i++) {
            if (st & (1 << i)) {
                tmp |= x[i];
            }
        }
        b[top++] = tmp;
    }
    sort(b, b + top);
    for (int i = 0; i < top; i++) {
        cout << b[i] << endl;
    }

    return 0;
}