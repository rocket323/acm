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
ll p[maxl], s[maxl];
int t;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        
        p[0] = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            p[i] = p[i - 1] + a[i];
        }
        s[n + 1] = 0;
        for (int i = n; i >= 1; --i) {
            s[i] = s[i + 1] + a[i];
        }

        int idx = 0;
        for (int i = 1; i <= n; ++i) {
            ll tmp = p[i] + s[i];
            if (idx == 0 || tmp < p[idx] + s[idx])
                idx = i;
        }
        printf("%d\n", idx);
    }

    return 0;
}


