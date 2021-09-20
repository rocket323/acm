#include <stdio.h>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <map>
using namespace std;
using ll = long long;
using pii = pair<ll, ll>;

const ll inf = 1e18;
const int maxl = 2e5 + 10;
ll a, b;
ll k;
string s;
set<pii> ps;
map<pii, vector<ll>> mp;

void go(ll &x, ll &y, char ch) {
    if (ch == 'L') x--;
    else if (ch == 'R') x++;
    else if (ch == 'U') y--;
    else if (ch == 'D') y++;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >>  s;
    cin >> k;

    ll x = 0, y = 0;
    ps.insert(make_pair(x, y));
    for (int i = 0; i < s.length(); i++) {
        go(x, y, s[i]);
        ps.insert(make_pair(x, y));
    }
    a = x, b = y;

    ll ans = 0;
    if (a == 0 && b == 0) {
        ans = ps.size();
    } else {
        for (auto [x, y] : ps) {
            ll q = 0;
            if (a != 0) {
                q = (x + maxl * a) / a - maxl;
            } else {
                q = (y + maxl * b) / b - maxl;
            }
            x -= q * a;
            y -= q * b;
            mp[make_pair(x, y)].push_back(q);
        }

        for (auto &&kv : mp) {
            auto &&v = kv.second;
            sort(v.begin(), v.end());
            for (int i = 0; i < v.size() - 1; i++) {
                ans += min(k, v[i+1] - v[i]);
            }
            ans += k;
        }
    }
    cout << ans << endl;

    return 0;
}

