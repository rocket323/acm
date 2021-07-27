#include <bits/stdc++.h>

int n;
int c[5000], d[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int calc(int n) {
    if (n == 0)
        return d[0];
    int ans = 0;
    while (n > 0) {
        ans += d[n % 10];
        n /= 10;
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    int ans = 0;
    for (int i = 0; i < 2000; i++)
        c[i] = calc(i);
    for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j <= 1000; j++) {
            int k = i + j;
            if (c[i] + c[j] + c[k] + 4 == n)
                ans++;
        }
    }
    printf("%d\n", ans);
}
