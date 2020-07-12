#include <stdio.h>
#include <cstring>
#include <sstream>

int main() {

    int n;
    char s[1000];
    scanf("%d", &n);
    int ans = 0;
    while (scanf("%s", s) != EOF) {
        int tmp = 0;
        for (int i = 0; s[i]; ++i) {
            if (s[i] >= 'A' && s[i] <= 'Z')
                tmp++;
        }
        if (tmp > ans) ans = tmp;
    }
    printf("%d\n", ans);

    return 0;
}

