#include <stdio.h>
#include <cstring>
#include <vector>
#include <cmath>
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

int BS = 0;
int c1[35][maxl], n, m;
int a[maxl];

int lowbit(int x) { return x & -x; }

void add(int c[], int n) {
    n += 2;
    while (n < maxl) {
        c[n]++;
        n += lowbit(n);
    }
}

int query(int c[], int n) {
    int ans = 0;
    for (n += 2; n; n -= lowbit(n)) {
        ans += c[n];
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &m);

    memset(c1, 0, sizeof c1);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        
        for (int j = 0; j < 31; j++) {
            if (a[i] & (1 << j))
                add(c1[j], i);
        }
    }

    for (int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        unsigned ans = 0;
        
        for (int j = 0; j < 31; j++) {
            int cc1 = query(c1[j], r) - query(c1[j], l - 1);
            int cc0 = (r - l + 1) - cc1;

            if (cc0 > cc1)
                ans = ans + (1 << j);
        }
        printf("%d\n", ans);
    }

    return 0;
}

