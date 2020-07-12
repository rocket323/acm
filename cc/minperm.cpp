#include <stdio.h>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 1e9 + 7;

int n, a[maxl];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        if (n & 1) {
            for (int i = 1; i + 1 <= n - 3; i += 2) {
                a[i] = i + 1;
                a[i + 1] = i;
            }
            a[n] = n - 2;
            a[n - 1] = n;
            a[n - 2] = n - 1;
        } else {
            for (int i = 1; i + 1 <= n; i += 2) {
                a[i] = i + 1;
                a[i + 1] = i;
            }
        }
        for (int i = 1; i <= n; ++i)
            printf("%d%c", a[i], (i == n) ? '\n' : ' ');
    }

    return 0;
}


