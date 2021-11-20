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

int n, x[maxl], y[maxl];
set<pair<int, int>> s;

int gcd(int a, int b) {
    if (a < b) {
        swap(a, b);
    }
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                continue;
            int dx = x[j] - x[i];
            int dy = y[j] - y[i];
            // puts("h1");
            // printf("x %d %d\n", dx, dy);
            int d = gcd(abs(dx), abs(dy));
            // puts("h2");
            if (d == 0) {
                // printf("%d %d\n", dx, dy);
                // puts("f");
                return 0;
            }
            // printf("%d %d %d\n", dx, dy, d);
            dx /= d;
            dy /= d;
            s.insert({dx, dy});
        }
    }
    cout << s.size() << endl;

    return 0;
}

