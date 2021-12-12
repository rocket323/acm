#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

struct node {
    int a, b, c;
} e[maxl], eb[maxl];

int n, b[maxl], top;
int c[maxl], m;

bool cmp(const node &a, const node &b) {
    if (a.a != b.a)
        return a.a < b.a;
    return a.b > b.b;
}

int lowbit(int x) {
    return x & -x;
}

void add(int n, int v) {
    n += 2;
    while (n < maxl) {
        c[n] = (c[n] + v);
        n += lowbit(n);
    }
}

int sum(int n) {
    n += 2;
    int ans = 0;
    while (n) {
        ans = (ans + c[n]);
        n -= lowbit(n);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &e[i].a);
        e[i].c = 1;
    }
    top = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &e[i].b);
        b[top++] = e[i].b;
    }
    sort(e + 1, e + 1 + n, cmp);
    sort(b, b + top);
    top = unique(b, b + top) - b;
    ll ans = 0;
    m = 0;
    for (int i = 1; i <= n; i++) {
        if (m == 0 || !(e[i].a == eb[m - 1].a && e[i].b == eb[m - 1].b)) {
            eb[m++] = e[i];
        } else {
            eb[m - 1].c++;
        }
    }

    int all = 0;
    for (int i = 0; i < m; i++) {
        int x = lower_bound(b, b + top, eb[i].b) - b;
        int tmp = all - sum(x - 1);
        ans = ans + (ll)tmp * eb[i].c;
        ans = ans + (ll)eb[i].c * eb[i].c;
        all += eb[i].c;
        add(x, eb[i].c);
    }
    cout << ans << endl;

    return 0;
}

