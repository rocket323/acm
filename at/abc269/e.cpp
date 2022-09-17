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

int n;
int a, b, c, d;

int main() {
    scanf("%d", &n);
    a = 1, b = n;
    c = 1, d = n;
    while (a < b) {
        int mid = (a + b) / 2;
        printf("? %d %d %d %d\n", a, mid, c, d);
        fflush(stdout);
        int t;
        scanf("%d", &t);
        if (t < mid - a + 1) {
            b = mid;
        } else {
            a = mid + 1;
        }
    }
    while (c < d) {
        int mid = (c + d) / 2;
        printf("? %d %d %d %d\n", 1, n, c, mid);
        fflush(stdout);
        int t;
        scanf("%d", &t);
        if (t < mid - c + 1) {
            d = mid;
        } else {
            c = mid + 1;
        }
    }
    printf("! %d %d\n", a, c);
    fflush(stdout);
    return 0;
}