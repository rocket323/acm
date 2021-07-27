#include <bits/stdc++.h>
using namespace std;

int n;
int f[1024];

int main() {
    scanf("%d", &n);
    f[1] = 1;

    for (int i = 2; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j <= i / 2; j++) {
            f[i] += f[j];
        }
    }

    printf("%d\n", f[n]);
    return 0;
}
