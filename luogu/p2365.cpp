#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <cmath>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;

struct Line {
    ll k, b;
    Line(ll k_ = 0, ll b_ = 0) : k(k_), b(b_) {}
    ll eval(int x) {
        return k * x + b;
    }
    friend bool bad(const Line &l1, const Line &l2, const Line &l3) {
        /*
            intersection(l1,l2) has x-coordinate x' = (b1-b2)/(k2-k1)
            intersection(l1,l3) has x-coordinate x'' = (b1-b3)/(k3-k1)
            x' > x'' <=> (b1-b2)/(k2-k1) > (b1-b3)/(k3-k1)
        */
        return (l1.b - l2.b) * (l3.k - l1.k) > (l1.b - l3.b) * (l2.k - l1.k);
    }
};

struct Cht {
    void add(const Line &l) {
        while (tail - head >= 2 && bad(st[tail-2], st[tail-1], l)) {
            tail--;
        }
        st[tail++] = l;
    }
    ll query(int x) {
        while (p + 1 < tail && st[p+1].eval(x) < st[p].eval(x))
            p++;
        return st[p].eval(x);
    }

    Line st[maxl];
    int head = 0, tail = 0, p = 0;
};

ll f[maxl], g[maxl];
ll n, s, t[maxl], c[maxl];
Cht cht;

int main() {
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> c[i];
        t[i] += t[i-1];
        c[i] += c[i-1];
    }

    f[0] = 0;
    cht.add({0, s * c[n]});
    for (int i = 1; i <= n; i++) {
        f[i] = cht.query(t[i]) + t[i] * c[i];
        cht.add({-c[i], f[i] + s * (c[n] - c[i])});
    }

    cout << f[n] << endl;
    return 0;
}

