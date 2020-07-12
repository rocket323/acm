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

ll n, d, t;
ll v, c;

ll ds(ll n) {
    ll ans = 0;
    while (n > 0) {
        ans += n % 10;
        n /= 10;
    }
    return ans;
}

void update(ll cv, ll cc) {
    if (v == -1 || cv < v) {
        v = cv, c = cc;
    } else if (cv == v && cc < c) {
        v = cv, c = cc;
    }
}

void dfs(ll dep, ll n, ll cnt) {
    update(n, cnt);
    if (dep >= 20)
        return;

    dfs(dep + 1, n + d, cnt + 1);
    dfs(dep + 1, ds(n), cnt + 1);
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> d;
        v = -1, c = 0;

        ll cnt = 0;
        dfs(0, n, cnt);

        cout << v << ' ' << c << endl;
    }

    return 0;
}

