#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 100010;
const int mod = 163577857;

int f[600][600];
int n, k;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &k);
        memset(f, 0, sizeof f);

        for (int i = 1; i <= min(k, 500); i++) {
            for (int j = 1; j <= min(n, 500); j++) {
                if (i < k)
                    f[i][j] = f[i-1][j];
                for (int x = 1; x <= j; x++) {
                    int tmp =(ll)(j - x + 1) * (f[i-1][j-x] + 1) % mod;
                    f[i][j] = (f[i][j] + tmp) % mod;
                }
            } 
        }
        printf("%d\n", f[k][n]);
    }

    return 0;
}

