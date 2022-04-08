#include <bits/stdc++.h>
using namespace std;

const int maxl = 1e5 + 10;
int n, a[maxl], t, q, x;

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }

        scanf("%d", &q);
        sort(a, a + n);
        for (int i = 0; i < q; i++) {
            scanf("%d", &x);
            int p = upper_bound(a, a + n, x) - a;
            printf("%d\n", p);
        }
    }
    return 0;
}
