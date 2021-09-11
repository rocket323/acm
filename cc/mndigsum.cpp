#include <stdio.h>
#include <cstring>

const int X = 31623;
int t, n, l, r;
int sum, base;

void update(int b, int x) {
    if (x < sum) {
        sum = x;
        base = b;
    }
}

int calc(int b) {
    int x = n, ans = 0;
    while (x) {
        ans += x % b;
        x /= b;
    }
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &l, &r);
        sum = 1e9 + 10;
        base = 1e9 + 10;
        for (int i = l; i <= X && i <= r; i++) {
            int x = calc(i);
            update(i, x);
        }

        if (n < r) {
            update(r, n);
        }

        for (int i = 1; i <= X; i++) {
            int b = n / i;
            if (b < l)
                continue;

            if (b > r)
                b = r;
            int c = n - b * i;

            if (b > X && c < b) {
                update(b, i + c);
            }
        }

        printf("%d\n", base);
    }
}
