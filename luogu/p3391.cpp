#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>

const int maxe = 3e5;
const int maxl = 1e5 + 10;
const int inf = 0x7fffffff;

int n, m;
std::vector<int> ans;
int a[maxl];

class Splay {
public:
    struct Node {
        int ch[2];
        int size, fa;
        bool rev;
        int val;
    } t[maxe];

    int mset_;
    int root_;

    Splay() : mset_(0), root_(0) {
        memset(&t[0], 0, sizeof(Node));
        t[0].val = -inf;
        int nd = newNode(0, 0, -inf);
        nd = newNode(nd, 1, -inf);
        splay(nd, 0);
    }

    int newNode(int fa, int d, int val) {
        int nd = ++mset_;
        if (fa) {
            t[fa].ch[d] = nd;
        }
        t[nd].ch[0] = t[nd].ch[1] = 0;
        t[nd].size = 1;
        t[nd].fa = fa;
        t[nd].rev = false;
        t[nd].val = val;
        return nd;
    }

    int get(int x) {
        return t[t[x].fa].ch[1] == x;
    }

    void up(int x) {
        Node *p = &t[x], *lc = &t[t[x].ch[0]], *rc = &t[t[x].ch[1]];
        p->size = lc->size + rc->size + 1;
    }

    void down(int x) {
        if (x == 0)
            return;

        Node *p = &t[x], *lc = &t[t[x].ch[0]], *rc = &t[t[x].ch[1]];
        if (p->rev) {
            p->rev = false;
            lc->rev ^= 1;
            rc->rev ^= 1;
            std::swap(p->ch[0], p->ch[1]);
        }
    }

    void attach(int x, int fa, int d) {
        t[fa].ch[d] = x;
        t[x].fa = fa;
    }

    void rotate(int x) {
        int fa = t[x].fa, gfa = t[fa].fa;
        int d1 = get(x), d2 = get(fa);
        down(t[x].ch[0]);
        down(t[x].ch[1]);
        down(t[fa].ch[d1 ^ 1]);
        attach(t[x].ch[d1 ^ 1], fa, d1);
        attach(x, gfa, d2);
        attach(fa, x, d1 ^ 1);
        up(fa);
        up(x);
    }

    void splay(int x, int goal) {
        down(x);
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

    int select(int k, int fa) {
        int nd = root_;
        while (true) {
            down(nd);
            int son = t[nd].ch[0];
            if (k <= t[son].size) {
                nd = son;
            } else if (k > t[son].size + 1) {
                k -= t[son].size + 1;
                nd = t[nd].ch[1];
            } else {
                break;
            }
        }

        splay(nd, fa);
        return nd;
    }

    void insert(int p, int a[], int n) {
        int head = 0, tail = 0;
        head = tail = newNode(0, 1, a[0]);
        for (int i = 1; i < n; i++) {
            tail = newNode(tail, 1, a[i]);
        }

        int l = select(p + 1, 0);
        int r = select(p + 2, l);
        t[r].ch[0] = head;
        t[head].fa = r;
        splay(tail, 0);
    }

    void swap(int a, int b) {
        int l = select(a, 0);
        int r = select(b + 2, l);
        t[t[r].ch[0]].rev ^= 1;
        splay(t[r].ch[0], 0);
    }

    void out(int x) {
        if (x == 0)
            return;
        down(x);
        out(t[x].ch[0]);
        ans.push_back(t[x].val);
        out(t[x].ch[1]);
    }
} s;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    s.insert(0, a, n);

    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        s.swap(l, r);
    }
    s.out(s.root_);
    for (int i = 1; i < ans.size() - 1; i++) {
        printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
    }
    return 0;
}
