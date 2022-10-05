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

int n, a[maxl], t, q;
int idx, m;
ll sum;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            sum += a[i];
        }
        scanf("%d", &q);
        idx = 0;
        m = a[0];
        for (int i = 0; i < q; i++) {
            int op, x;
            scanf("%d%d", &op, &x);
            if (op == 1) {
                a[n++] = x;
                sum += x;
            } else {
                while (x > 0) {
                    if (m > x) {
                        m -= x;
                        x = 0;
                    } else if (x >= sum && sum > 0) {
                        x %= sum;
                    } else {
                        x -= m;
                        idx++;
                        if (idx == n)
                            idx = 0;
                        m = a[idx];
                    }
                }
                printf("%d\n", idx + 1);
            }
        }
    }

    return 0;
}