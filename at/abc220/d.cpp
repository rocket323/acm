#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxl = 1e5 + 10;
const int mod = 998244353;
int n, f[maxl][10], a[maxl];

int main() {
    memset(f, 0, sizeof f);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    f[0][a[0]] = 1;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < 10; j++) {
            int k = (j + a[i+1]) % 10;
            f[i+1][k] = ((long long)f[i+1][k] + f[i][j]) % mod;

            k = (j * a[i+1]) % 10;
            f[i+1][k] = ((long long)f[i+1][k] + f[i][j]) % mod;
        }
    }

    for (int i = 0; i < 10; i++) {
        printf("%d\n", f[n-1][i]);
    }

    return 0;
}

