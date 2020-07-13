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

class Splay {
public:
    struct Node {
        int ch[2];
        int size, val, fa;
        int flag;
    } t[maxe];

    int mset_;
    int root_;

    Splay() : mset_(0), root_(0) {
        int nd = newNode(0, 0, -inf);
        nd = newNode(nd, 1, -inf);
    }

    int newNode(int fa, int d, int val) {
        int nd = ++mset_;
        if (fa) {
            t[fa].ch[d] = nd;
        }
        t[nd].size = 1;
        t[nd].fa = fa;
        t[nd].val = val;
        t[nd].flag = 0;
        splay(nd, 0);
        return nd;
    }

    int get(int x) {
        return t[t[x].fa].ch[1] == x;
    }

    void up(int x) {
        t[x].size = t[t[x].ch[0]].size + t[t[x].ch[1]].size + 1;
    }

    void down(int nd) {
        if (nd == 0 || !t[nd].flag)
            return;
        t[nd].flag = 0;
        t[t[nd].ch[0]].flag ^= 1;
        t[t[nd].ch[1]].flag ^= 1;
        std::swap(t[nd].ch[0], t[nd].ch[1]);
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
            down(nd);
            int son = t[nd].ch[0];
            if (k <= t[son].size) {
                nd = son;
            } else if (k > t[son].size + 1) {
                k -= t[son].size + 1;
                nd = t[nd].ch[1];
            } else {
                return nd;
            }
        }
    }

    int size() {
        return t[root_].size - 2;
    }

    void append(int val) {
        insert(val, size());
    }

    void insert(int val, int p) {
        int x = kth(p + 1), y = kth(p + 1 + 1);
        splay(x, 0);
        splay(y, x);
        newNode(y, 0, val);
    }

    void swap(int l, int r) {
        int x = kth(l - 1 + 1), y = kth(r + 1 + 1);
        splay(x, 0);
        splay(y, x);
        int nd = t[y].ch[0];
        t[nd].flag ^= 1;
    }

    void out(int nd) {
        if (nd == 0)
            return;
        down(nd);
        out(t[nd].ch[0]);
        ans.push_back(t[nd].val);
        out(t[nd].ch[1]);
    }
} s;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        s.append(i);
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
