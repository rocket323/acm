#include <stdio.h>
#include <cstring>
#include <algorithm>

using namespace std;

int a[30], t, n;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &a[0], &a[1]);

        int x = a[0] | a[1];
        for (int i = 2; i <= min(n, 20); i++) {
            a[i] = (a[i - 1] + a[i - 2]) & 1023;
            x |= a[i];
        }

        int ans = 0;
        while (x) {
            if ((x & 1) == 0)
                ans++;
            x >>= 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
