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
const int maxl = 200010;
const int mod = 1e9 + 7;

int n, a[maxl];
ll s1[maxl], s2[maxl];

struct Line {
    ll k, b;
    Line(ll _k = 0, ll _b = 0): k(_k), b(_b) {}
    ll eval(ll x) {
        return k * x + b;
    }
    friend bool isBefore(const Line &l1, const Line &l2, const Line &l3) {
        return (l3.b - l1.b) * (l1.k - l2.k) < (l2.b - l1.b) * (l1.k - l3.k);
    }
};

struct Cht {
    Cht(): head(0), tail(0) {}

    void add(const Line &l) {
        while (tail - head >= 2 && isBefore(st[tail - 2], st[tail - 1], l)) {
            tail--;
        }
        st[tail++] = l;
    }

    ll query(ll x) {
        int l = head, r = tail - 2, p = tail - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (st[mid].eval(x) >= st[mid + 1].eval(x)) {
                p = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }

        return st[p].eval(x);
    }

    Line st[maxl];
    int head, tail;
};

int main() {
    while (scanf("%d", &n) != EOF) {
        s1[0] = s2[0] = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            s1[i] = s1[i - 1] + a[i];
            s2[i] = s2[i - 1] + (ll)a[i] * i;
        }

        Cht cht;
        cht.add({0, 0});
        ll ans = 0;
        for (int i = 1; i <= n; ++i) {
            ll tmp = cht.query(0 - s1[i]) + s2[i];
            ans = max(ans, tmp);
            cht.add({i, (ll)i * s1[i] - s2[i]});
            // printf("%d %lld\n", i, tmp);
        }

        cout << ans << endl;
    }

    return 0;
}

