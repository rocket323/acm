#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
// using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;
const ll mod2 = 998244353;

ll pow(ll a, ll n, ll mod) {
    ll ans = 1, t = a % mod;
    while (n) {
        if (n & 1) {
            ans = ((ll)ans * t) % mod;
        }   
        t = ((ll)t * t) % mod;
        n >>= 1;
    }   
    return ans % mod;
}

int main() {
    ll n, k, m;
    std::cin >> n >> k >> m;
    ll pi = mod2 - 1;
    ll b = pow(k, n, pi);
    ll x = pow(m, b, mod2);
    if (m % mod2 == 0)
        x = 0;
    std::cout << x << std::endl;

    return 0;
}

