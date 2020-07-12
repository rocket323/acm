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

ll n, m;

ll gcd(ll a, ll b) {
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    ll d = gcd(a, b);
    return a / d * b;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // vector<int> v = {2, 3, 5, 5, 7, 8, 7, 9, 11, 39};

    int x = 0;
    while (cin >> n >> m) {
        ll d = gcd(n - 1, m - 1);
        ll total = lcm(n - 1, m - 1) + 1;
        ll side = (n + m - 2) / d;
        ll cross = (total - 1) / d + 1 - side;
        ll ans = total - cross;
        // cout << n << ' ' << m << ' ' << (t - v[x]) / 2 << endl;
        x++;
        cout << ans << endl;
    }

    return 0;
}

