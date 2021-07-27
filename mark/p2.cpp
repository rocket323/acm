#include <bits/stdc++.h>
using namespace std;

int t, n, c0, c1, c2, a;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        c0 = c1 = c2 = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            if (a > 0)
                c1++;
            else if (a < 0)
                c2++;
            else
                c0++;
        }
        if (c1 > c2)
            swap(c1, c2);

        if (c1 + c0 + 1 >= c2)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
