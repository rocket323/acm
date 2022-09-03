#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

struct node {
    int a;
    ll sum;
    int u;
};

bool operator<(const node &a, const node &b) {
    if (a.sum != b.sum)
        return a.sum < b.sum;
    if (a.a != b.a)
        return a.a > b.a;
    return a.u < b.u;
}

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int n, m, a[maxl];
vector<int> adj[maxl];
ll s[maxl], sum, t[maxl];
ll st[maxl];
int top, mark[maxl];

bool check(ll limit) {
    memset(mark, 0, sizeof mark);
    top = 0;
    for (int i = 1; i <= n; i++) {
        t[i] = s[i];
        if (t[i] <= limit) {
            st[top++] = i;
            mark[i] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (top == 0)
            return false;
        int u = st[--top];
        for (int v : adj[u]) {
            if (mark[v])
                continue;
            t[v] -= a[u];
            if (t[v] <= limit) {
                st[top++] = v;
                mark[v] = 1;
            }
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sum += (ll)a[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        s[u] += a[v];
        s[v] += a[u];
    }
    ll l = 0, r = sum;
    ll ans = sum;
    while (l <= r) {
        ll mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}