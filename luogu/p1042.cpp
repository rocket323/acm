#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;

char s[maxl], t[2505];
int n, stop;

void gao(int m) {
    int a = 0, b = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'W')
            a++;
        else
            b++;
        if (max(a, b) >= m && abs(a - b) > 1) {
            printf("%d:%d\n", a, b);
            a = b = 0;
        }
    }
    printf("%d:%d\n", a, b);
}

int main() {
    n = 0;
    while (scanf("%s", t) != EOF) {
        for (int i = 0; t[i]; i++) {
            s[n++] = t[i];
            if (s[n - 1] == 'E')
                break;
        }
        if (s[n - 1] == 'E')
            break;
    }
    s[n] = 0;

    gao(11);
    puts("");
    gao(21);

    return 0;
}
