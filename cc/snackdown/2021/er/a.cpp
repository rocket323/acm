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

int t, n, a[maxl], b[maxl], sb[maxl];
int k;

bool gao0(int a[], int l, int r) {
    for (int i = l; i <= r; i++) {
        if (a[i] != i)
            return false;
    }
    return true;
}

bool gao1() {
    if (k >= n)
        return true;
    memset(b, 0, sizeof b);
    memset(sb, 0, sizeof sb);
    for (int i = 1; i <= n; i++) {
        if (a[i] != i)
            b[i] = 1;
        sb[i] = sb[i-1] + b[i];
    }
    sb[n+1] = sb[n];
    for (int i = 1; i + k - 1 <= n; i++) {
        bool can = true;
        if (sb[i - 1] > 0 || sb[n + 1] - sb[i + k - 1] > 0) {
            can = false;
        }
        if (can)
            return true;
    }
    return false;
}

bool gao2() {
    int l = 1, r = n;
    while (l < n && a[l] == l)
        l++;
    while (r > 1 && a[r] == r)
        r--;

    for (int i = 1; i <= n; i++)
        b[i] = a[i];
    sort(b + l, b + l + k);
    sort(b + (r - k + 1), b + r + 1);
    if (gao0(b, l, r))
        return true;

    for (int i = 1; i <= n; i++)
        b[i] = a[i];
    sort(b + (r - k + 1), b + r + 1);
    sort(b + l, b + l + k);
    if (gao0(b, l, r))
        return true;

    return false;
}

bool gao22() {
    int c1 = 0, c2 = 0;
    int x = n - k;
    for (int i = 1; i <= x; i++) {
        if (a[i] > k)
            c1++;
    }
    for (int i = n; i >= n - x + 1; i--) {
        if (a[i] <= n - k)
            c2++;
    }
    if (c1 == 0 || c2 == 0)
        return true;
    return false;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        if (gao0(a, 1, n)) {
            puts("0");
        } else if (gao1()) {
            puts("1");
        } else if (gao2()) {
            puts("2");
        } else {
            puts("3");
        }
    }
    return 0;
}

