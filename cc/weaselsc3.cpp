#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <assert.h>
#include <set>
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;
#define maxl 100010
#define ll long long
const int mod = 1e9 + 7;
 
int t, n, a[maxl], k;
ll ans;
int l[maxl], r[maxl];
ll f[55][maxl], bb[maxl];
// vector<int> adj[maxl];

struct Edge {
    int idx;
    Edge *next;
} adj[maxl], memo[maxl * 3];

int mset;

void addEdge(int u, int v) {
    Edge *ptr = &memo[mset++];
    ptr->idx = v;
    ptr->next = adj[u].next;
    adj[u].next = ptr;
}
 
struct Line {
    ll k, b;
    Line(ll _k = 0, ll _b = 0): k(_k), b(_b) {}
    ll eval(ll x) {
        return k * x + b;
    }
    friend bool isBefore(const Line &l1, const Line &l2, const Line &l3) {
        // return (l3.b - l1.b) * (l1.k - l2.k) < (l2.b - l1.b) * (l1.k - l3.k);
        return (l3.b - l1.b) / (l1.k - l3.k) < (l2.b - l1.b) / (l1.k - l2.k);
    }
};
 
struct Cht {
    Cht(): top(0), pos(0) {}
    void clear() {
        top = 0;
    }
 
    void add(const Line &l, Line *tmp = NULL) {
        if (top > 0 && st[top - 1].k == l.k) {
            if (tmp != NULL)
                *tmp = st[top - 1];
 
            if (l.b > st[top - 1].b) {
                st[top - 1] = l;
            }
            return;
        }
 
        while (top >= 2 && isBefore(st[top - 2], st[top - 1], l))
            top--;
 
        if (tmp != NULL)
            *tmp = st[top];
        st[top++] = l;
    }
    ll query(ll x) {
        /*
        if (pos >= top) pos = top - 1;
        while (pos + 1 < top && st[pos + 1].eval(x) > st[pos].eval(x))
            pos++;
        return st[pos].eval(x);
        */

        int l = 0, r = top - 2, p = top - 1;
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
    int top;
    int pos;
};
 
Cht cht;
 
void dfs(int x, int i) {
    int top = cht.top;
    if (top == 0)
        f[x][i] = 0;
    else
        f[x][i] = cht.query(l[i]) + (ll)a[i] * (i - l[i]);
 
    Line line(a[i], f[x - 1][i] - (ll)a[i] * i);
 
    Line tmp;
    cht.add(line, &tmp);
    int pos = cht.top - 1;
    int last = cht.pos;
 
    for (Edge *ptr = adj[i].next; ptr; ptr = ptr->next) {
        dfs(x, ptr->idx);
    }
 
    cht.st[pos] = tmp;
    cht.top = top;
    cht.pos = last;
}
 
ll solve() {
    // clock_t t1 = clock();
    mset = 0;
    for (int i = 0; i <= n; ++i) {
        adj[i].next = NULL;
    }
    memset(f, 0, sizeof f);
 
    for (int i = 1; i <= n; ++i) {
        l[i] = i - 1;
        while (a[l[i]] >= a[i] && l[i] >= 1)
            l[i] = l[l[i]];
 
        // adj[l[i]].push_back(i);
        addEdge(l[i], i);
    }
    for (int i = n; i >= 1; --i) {
        r[i] = i + 1;
        while (a[r[i]] >= a[i] && r[i] <= n)
            r[i] = r[r[i]];
    }
 
    cht.clear();
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        f[1][i] = (ll)a[i] * (i - l[i]);
        ans = max(ans, f[1][i] + (ll)a[i] * (r[i] - i - 1));

        bb[i] = (ll)a[i] * (r[i] - i - 1);
    }

    // clock_t t2 = clock();
 
    for (int i = 2; i <= k + 1; ++i) {
        dfs(i, 0);
        for (int j = 1; j <= n; ++j) {
            ans = max(ans, f[i][j] + bb[j]);
        }
    }

    // clock_t t3 = clock();

    // printf("t2 - t1: %f, t3 - t2: %f\n", (t2 - t1) * 1.0 / CLOCKS_PER_SEC, (t3 - t2) * 1.0 / CLOCKS_PER_SEC);
    return ans;
}
 
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        memset(a, 0, sizeof a);
        for (int i = 1; i <= n; ++i)
            scanf("%d", &a[i]);
 
        ll ans = solve();
        reverse(a + 1, a + 1 + n);
        ans = max(ans, solve());
 
        printf("%lld\n", ans);
    }
 
    return 0;
}

