#include <stdio.h>
#include <cstring>

char s[200][200], t[200][200];
int n, m;

bool check(char s[][200], int n, int m) {
    if (n % 3) return false;
    int d = n / 3;
    char a = s[0][0], b = s[d][0], c = s[2*d][0];
    if (a == b || b == c || a == c)
        return false;

    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < m; ++j) {
            if (s[i][j] != a) return false;
            if (s[i+d][j] != b) return false;
            if (s[i+2*d][j] != c) return false;
        }
    }
    return true;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        for (int i = 0; i < n; ++i)
            scanf("%s", s[i]);

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                t[i][j] = s[j][i];

        if ((check(s, n, m)) || check(t, m, n))
            puts("YES");
        else
            puts("NO");
    }

    return 0;
}

