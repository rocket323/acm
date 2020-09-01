#include <bits/stdc++.h>

const int maxl = 1e5 + 10;
int t, n;
char s[maxl];
int c0, c1;

void solve(int d, char ch) {
    if (d == 0) {
        printf("%d %d\n", 1, n);
        return;
    }

    int c0 = 0, c1 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == ch) {
            c0++;
        } else {
            c1++;
        }

        if (c0 - c1 >= d) {
            printf("%d %d\n", 1, i + 1);
            return;
        }
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        c0 = c1 = 0;

        n = strlen(s);
        for (int i = 0; i < n; i++) {
            if (s[i] == '0')
                c0++;
            else
                c1++;
        }

        if (c1 > c0) {
            solve((c1 - c0) / 2, '1');
        } else {
            solve((c0 - c1) / 2, '0');
        }
    }
}
