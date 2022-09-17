#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

char s[20][20];
int a, b, c, d;

int main() {
    for (int i = 0; i < 10; i++) {
        scanf("%s", s[i]);
    }
    a = b = c = d = -1;
    for (int i = 1; i <= 10 && a == -1; i++) {
        for (int j = 1; j <= 10; j++) {
            if (s[i - 1][j - 1] == '#') {
                a = i;
                c = j;
                break;
            }
        }
    }
    for (int i = 10; i >= 1 && b == -1; i--) {
        for (int j = 10; j >= 1; j--) {
            if (s[i - 1][j - 1] == '#') {
                b = i;
                d = j;
                break;
            }
        }
    }
    printf("%d %d\n", a, b);
    printf("%d %d\n", c, d);
    return 0;
}