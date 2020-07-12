#include <stdio.h>
#include <cstring>
#define ll long long
#define maxl 100010

const int mod = 1e9 + 7;
int n, m, a[maxl], c1[maxl], c2[maxl];
int pw[maxl];

int lowbit(int n) {
    return n & -n;
}

void add(int c[], int n, int v) {
    n += 1;
    while (n < maxl) {
        c[n] = (c[n] + v) % mod;
        n += lowbit(n);
    }
}

int getSum(int c[], int n) {
    int ans = 0;
    n += 1;
    while (n) {
        ans = (ans + c[n]) % mod;
        n -= lowbit(n);
    }
    return ans;
}

int main() {
    pw[0] = 1;
    for (int i = 1; i < maxl; ++i)
        pw[i] = (ll)pw[i - 1] * 2 % mod;

    while (scanf("%d%d", &n, &m) != EOF) {
        memset(a, 0, sizeof a);
        memset(c1, 0, sizeof c1);
        memset(c2, 0, sizeof c2);

        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            add(c1, i, (ll)a[i] * a[i] % mod);
        }
        for (int i = 1; i < n; ++i)
            add(c2, i, (ll)a[i] * a[i + 1] % mod);

        for (int i = 0; i < m; ++i) {
            int op, x, y;
            scanf("%d%d%d", &op, &x, &y);
            if (op == 1) {
                int prev = mod - (ll)a[x] * a[x] % mod;
                int now = (ll)y * y % mod;
                add(c1, x, (prev + now) % mod);

                prev = mod - (ll)a[x] * a[x + 1] % mod;
                now = (ll)y * a[x + 1] % mod;
                add(c2, x, (prev + now) % mod);

                prev = mod - (ll)a[x - 1] * a[x] % mod;
                now = (ll)y * a[x - 1] % mod;
                add(c2, x - 1, (prev + now) % mod);

                a[x] = y;
            } else {
                int l = y - x + 1;
                int num1 = (getSum(c1, y) - getSum(c1, x - 1) + mod) % mod;
                int num2 = (getSum(c2, y - 1) - getSum(c2, x - 1) + mod) % mod;

                num1 = (ll)num1 * pw[l - 1] % mod;
                num2 = (ll)num2 * pw[l - 1] % mod;

                printf("%d\n", (num1 - num2 + mod) % mod);
            }
        }
    }

    return 0;
}

