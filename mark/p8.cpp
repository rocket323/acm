#include <bits/stdc++.h>

int t, n, a1, a2;

int calc(int x) {
    int ans = 0;
    while (x) {
        ans += (x & 1);
        x >>= 1;
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &a1, &a2);
        int d = n % 3;
        if (d == 2) {
            printf("%d\n", calc(a1 + a2));
        } else if (d == 1) {
            printf("%d\n", calc(a1));
        } else {
            printf("0\n");
        }
    }
    return 0;
}
