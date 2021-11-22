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

int t, x, y;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &x, &y);
        if (y < x) {
            printf("%d\n", x - y);
        } else {
            if ((y - x) % 2 == 0) {
                printf("%d\n", (y - x) / 2);
            } else {
                printf("%d\n", (y - x) / 2 + 2);
            }
        }
    }
    return 0;
}
