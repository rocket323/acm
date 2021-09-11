#include <stdio.h>
#include <cstring>

int t, a, b, c, d, e;

bool check(int a, int b, int c, int d, int e) {
    if (a + b > d)
        return false;
    if (c > e)
        return false;
    return true;
}

bool solve() {
    if (check(a, b, c, d, e))
        return true;
    if (check(a, c, b, d, e))
        return true;
    if (check(b, c, a, d, e))
        return true;
    return false;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
        bool ans = solve();
        puts(ans ? "YES" : "NO");
    }
    return 0;
}
