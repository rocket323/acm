#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e5 + 10;

int t, n, a[maxl], p, q, x;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &x);
        int p = upper_bound(a, a + n, x) - a;
        printf("%d\n", p);
    }
    return 0;
}
