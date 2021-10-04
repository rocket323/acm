#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;
const int maxl = 1e5 + 10;
int st[20], top, n;

ll gao(int mask) {
    ll a = 0, b = 0, fa = -1, fb = -1;
    for (int i = top - 1; i >= 0; i--) {
        if (mask & (1 << i)) {
            a = a * 10 + st[i];
            if (fa == -1)
                fa = st[i];
        } else {
            b = b * 10 + st[i];
            if (fb == -1)
                fb = st[i];
        }
    }

    if (fa <= 0 || fb <= 0)
        return 0;
    return a * b;
}

int main() {
    ll ans = 0;
    while (scanf("%d", &n) != EOF) {
        top = 0;
        int m = n;
        while (m) {
            st[top++] = m % 10;
            m /= 10;
        }
        sort(st, st + top);

        for (int i = 0; i < (1<<top); i++) {
            ans = max(ans, gao(i));
        }

        cout << ans << endl;
    }

    return 0;
}

