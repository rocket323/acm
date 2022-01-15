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
const int maxl = 1e6 + 10;

int d[maxl], a, n;
queue<int> q;

void push(int x, int dist) {
    if (d[x] != -1)
        return;
    d[x] = dist;
    q.push(x);
}

int change(int x) {
    if (x < 10 || x % 10 == 0)
        return -1;
    int a = x % 10;
    int l = 1;
    while (l <= x)
        l *= 10;
    l /= 10;
    return a * l + x / 10;
}

int gao() {
    memset(d, -1, sizeof d);
    push(1, 0);

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (x == n)
            return d[x];

        if ((ll)x * a < 1e6)
            push((ll)x * a, d[x] + 1);

        int y = change(x);
        if (y > 0)
            push(y, d[x] + 1);
    }
    return -1;
}

int main() {
    scanf("%d%d", &a, &n);
    printf("%d\n", gao());
    return 0;
}
