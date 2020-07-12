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

struct Line {
    ll k, b;
    Line(ll _k = 0, ll _b = 0): k(_k), b(_b) {}
    ll eval(int x) {
        return k * x + b;
    }
    friend bool isBefore(const Line &l1, const Line &l2, const Line &l3) {
        return (l3.b - l1.b) * (l1.k - l2.k) < (l2.b - l1.b) * (l1.k - l3.k);
    }
};

struct Cht {
    Cht(): head(0), tail(0), p(0) {}

    void add(const Line &l) {
        while (tail - head >= 2 && isBefore(st[tail - 2], st[tail - 1], l)) {
            tail--;
        }
        st[tail++] = l;
    }

    ll query(int x) {
        if (p >= tail) p = tail - 1;
        while (p + 1 < tail && st[p + 1].eval(x) < st[p].eval(x))
            p++;

        return st[p].eval(x);
    }

    Line st[maxl];
    int head, tail, p;
};

Line st[maxl];
int head, tail;

struct Rect {
    int w, h;
} rect[maxl];

int n, top;
ll f[maxl];

int main() {
    while (scanf("%d", &n) != EOF) {
        Cht cht;
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d", &rect[i].w, &rect[i].h);
            f[i] = 1e18;
        }

        sort(rect + 1, rect + 1 + n, [&](const Rect &a, const Rect &b) {
            return a.h < b.h;
        });

        top = 0;
        for (int i = 1; i <= n; ++i) {
            while (top > 0 && rect[top].w <= rect[i].w)
                top--;
            rect[++top] = rect[i];
        }
        n = top;

        f[0] = 0;
        cht.add({rect[1].w, f[0]});
        for (int i = 1; i <= n; ++i) {
            f[i] = cht.query(rect[i].h);
            if (i < n)
                cht.add({rect[i + 1].w, f[i]});
        }

        printf("%lld\n", f[n]);
    }

    return 0;
}

