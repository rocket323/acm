#include <stdio.h>
#include <cstring>
#include <cmath>
#include <algorithm>

const int maxe = 3e5;
const int maxl = 1e5 + 10;
const int inf = 0x7fffffff;

int m, d, b, t;

class Splay {
public:
    Splay() : mset_(0), root_(0) {
        int nd = newNode(0, 0, -inf);
        nd = newNode(nd, 1, -inf);
    }

    int newNode(int fa, int d, int val) {
        int nd = ++mset_;
        if (fa) {
            t[fa].ch[d] = nd;
        }
        t[nd].size = t[nd].cnt = 1;
        t[nd].fa = fa;
        t[nd].val = val;
        t[nd].mx = val;
        splay(nd, 0);
        return nd;
    }

    int get(int x) {
        return t[t[x].fa].ch[1] == x;
    }

    void up(int x) {
        t[x].size = t[t[x].ch[0]].size + t[t[x].ch[1]].size + t[x].cnt;
        t[x].mx = std::max(std::max(t[t[x].ch[0]].mx, t[t[x].ch[1]].mx), t[x].val);
    }

    void attach(int x, int fa, int d) {
        t[fa].ch[d] = x;
        t[x].fa = fa;
    }

    void rotate(int x) {
        int fa = t[x].fa, gfa = t[fa].fa;
        int d1 = get(x), d2 = get(fa);
        attach(t[x].ch[d1 ^ 1], fa, d1);
        attach(x, gfa, d2);
        attach(fa, x, d1 ^ 1);
        up(fa);
        up(x);
    }

    void splay(int x, int goal) {
        while (t[x].fa != goal) {
            int fa = t[x].fa, gfa = t[fa].fa;
            int d1 = get(x), d2 = get(fa);
            if (gfa != goal) {
                if (d1 == d2)
                    rotate(fa);
                else
                    rotate(x);
            }
            rotate(x);
        }
        if (goal == 0)
            root_ = x;
    }

    int kth(int k) {
        int nd = root_;
        if (nd == 0 || t[nd].size < k)
            return nd;
        while (true) {
            int son = t[nd].ch[0];
            if (k <= t[son].size) {
                nd = son;
            } else if (k > t[son].size + t[nd].cnt) {
                k -= t[son].size + t[nd].cnt;
                nd = t[nd].ch[1];
            } else {
                return nd;
            }
        }
    }

    int size() {
        return t[root_].size - 2;
    }

    void insert(int val, int p) {
        int x = kth(p + 1), y = kth(p + 1 + 1);
        splay(x, 0);
        splay(y, x);
        newNode(y, 0, val);
    }

    int query(int l, int r) {
        int x = kth(l - 1 + 1), y = kth(r + 1 + 1);;
        splay(x, 0);
        splay(y, x);
        int nd = t[y].ch[0];
        return t[nd].mx;
    }

public:
    struct Node {
        int ch[2];
        int cnt, size, val, fa;
        int mx;
    } t[maxe];

    int mset_;
    int root_;
} s;

int main() {
    scanf("%d%d", &m, &d);
    t = 0;

    char a[10];
    int b;
    for (int i = 0; i < m; i++) {
        scanf("%s%d", a, &b);
        if (a[0] == 'A') {
            int x = (b + t) % d;
            s.insert(x, s.size());
        } else {
            int sz = s.size();
            int l = sz - b + 1;
            t = s.query(l, sz);
            printf("%d\n", t);
        }
    }

    return 0;
}
