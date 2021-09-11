#include <stdio.h>
#include <cstring>

const int maxl = 105;
int t, n, a, b;
char s[maxl];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &n, &a, &b);
        scanf("%s", s);
        int ans = 0;
        for (int i = 0; s[i]; i++) {
            if (s[i] == '0')
                ans += a;
            else
                ans += b;
        }
        printf("%d\n", ans);
    }
    return 0;
}
