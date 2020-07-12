#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define maxl 1010
#define mod 1000000007

int t, n, m, c[maxl][maxl];

int main() {
    scanf("%d", &t);
    c[0][0] = 1;
    for (int i = 1; i < maxl; ++i) {
        c[i][0] = c[i][i] = 1;
        for (int j = 1; j < i; ++j)
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
    }
    
    while (t--) {
        scanf("%d%d", &n, &m);
        if (n < m) swap(n, m);
        printf("%d\n", c[n][m]);
    }

    return 0;
}

