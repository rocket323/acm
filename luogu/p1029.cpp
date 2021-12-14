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

int x0, y0;

int gcd(int a, int b) {
    if (a < b)
        swap(a, b);
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    scanf("%d%d", &x0, &y0);
    int k = y0 / x0, ans = 0;
    if (y0 % x0)
        k = 0;
    for (int i = 1; i * i <= k; i++) {
        if (k % i != 0)
            continue;
        int j = k / i;
        if (gcd(i, j) == 1) {
            ans += 1 + (i != j);
        }
    }
    printf("%d\n", ans);

    return 0;
}
