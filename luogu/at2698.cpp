#include <stdio.h>
#include <cstring>

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;
char s[maxl], ans[maxl], t[maxl];
int f[maxl], p[maxl], nxt[maxl][26];
int n;

int main() {
    while (scanf("%s", s) != EOF) {
        n = strlen(s);
        for (int i = 0; i < 26; i++) nxt[n][i] = -1;
        for (int i = n-1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                nxt[i][j] = (s[i] == 'a' + j) ? i : nxt[i+1][j];
            }
        }

        memset(f, 0x3f, sizeof(f));
        f[n] = 1;
        ans[n] = 'a';
        p[n] = n + 1;
        // printf("%d\n", n);
        // for (int i = 0; i < 26; i++) {
        //     printf("%d\n", nxt[0][i]);
        // }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                if (nxt[i][j] == -1) {
                    f[i] = 1;
                    ans[i] = 'a' + j;
                    p[i] = n + 1;
                    break;
                }
            }
            if (f[i] == inf) {
                // printf("x %d\n", i);
                for (int j = 0; j < 26; j++) {
                    int x = nxt[i][j];
                    if (f[x+1] + 1 < f[i]) {
                        f[i] = f[x+1] + 1;
                        ans[i] = 'a' + j;
                        p[i] = x + 1;
                        // printf("y %d %d %d\n", i, x, f[x+1]);
                    }
                }
            }
        }
        int x = 0, top = 0;
        // printf("%d, %d\n", f[0], p[0]);
        while (x <= n) {
            // printf("x: %d, f[x]: %d, p: %d\n", x, f[x], p[x]);
            t[top++] = ans[x];
            x = p[x];
        }
        t[top] = 0;
        puts(t);
    }
    return 0;
}
