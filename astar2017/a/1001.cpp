#include <stdio.h>

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        n--;
        int ans = 0;
        for (int i = 1; (long long) i * i <= n; ++i) {
            if (n % i == 0) {
                if (n / i == i)
                    ans++;
                else
                    ans += 2;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}

