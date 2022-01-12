#include <algorithm>
#include <cmath>
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

int sq(int x) {
    return x * x;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int tmp = sq(x[i] - x[j]) + sq(y[i] - y[j]);
            if (tmp > ans)
                ans = tmp;
        }
    }
    printf("%.8lf\n", sqrt(ans));

    return 0;
}
