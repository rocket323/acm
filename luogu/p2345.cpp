#include <stdio.h>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

using ll = long long;
const int maxl = 2e4 + 10;

struct node {
    int v, x, ans;
} e[maxl];

int n;
ll ans;

bool cmpx(const node &a, const node &b) {
    return a.x < b.x;
}

bool cmpv(const node &a, const node &b) {
    return a.v > b.v;
}

void dfs(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    dfs(l, mid);
    dfs(mid + 1, r);

    sort(e + l, e + mid + 1, cmpv);
    sort(e + mid + 1, e + r + 1, cmpv);

    ll s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    ll tot3 = (mid - l + 1);
    ll tot4 = 0;
    for (int i = l; i <= mid; i++)
        tot4 += -e[i].x;

    int j = l;
    for (int i = mid + 1; i <= r; i++) {
        while (j <= mid && e[j].v > e[i].v) {
            s1 += e[j].v;
            s2 += -e[j].x * e[j].v;
            s3 += 1;
            s4 += -e[j].x;
            j++;
        }

        ans += e[i].x * s1 + s2 + e[i].v * e[i].x * (tot3 - s3) + e[i].v * (tot4 - s4);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &e[i].v, &e[i].x);
    }
    sort(e, e + n, cmpx);
    ans = 0;
    dfs(0, n - 1);
    cout << ans << endl;
    return 0;
}
