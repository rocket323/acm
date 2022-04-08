#include <bits/stdc++.h>
using namespace std;

const int maxl = 20;
int n, m, a[maxl], t;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i < (1 << n); i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    sum += a[j];
                }
            }
            if (sum % m == 0)
                ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
