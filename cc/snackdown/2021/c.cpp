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
const int mod = 998244353;

int n, a[maxl], c[maxl];

int lowbit(int n) {
    return n & -n;
}

void add(int n, int val) {
    n += 2;
    while (n < maxl) {
        c[n] += val;
        c[n] %= mod;
        n += lowbit(n);
    }
}

int sum(int n) {
    n += 2;
    int ans = 0;
    while (n) {
        ans += c[n];
        ans %= mod;
        n -= lowbit(n);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int ans = 1;
    for (int i = 0; i < n; i++) {
        int tmp = sum(a[i] - 1) + 1;
        ans = (ans + tmp) % mod;
        add(a[i], tmp);
    }
    printf("%d\n", ans);

    return 0;
}
