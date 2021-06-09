#include <bits/stdc++.h>
using namespace std;

int n, s, t, a[1000], d[1000];
std::queue<int> q;

void push(int x, int dist) {
    if (x < 1 || x > n || d[x] != -1) {
        return;
    }
    d[x] = dist;
    q.push(x);
}

int solve() {
    memset(d, -1, sizeof(d));
    q.push(s);
    d[s] = 0;

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (x == t) {
            return d[x];
        }

        push(x + a[x], d[x] + 1);
        push(x - a[x], d[x] + 1);
    }
    return -1;
}

int main() {
    scanf("%d%d%d", &n, &s, &t);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    printf("%d\n", solve());
    return 0;
}