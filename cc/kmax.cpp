#include <stdio.h>
#include <cstring>
#include <set>
#include <algorithm>
#define ll long long
#define maxl 100010
using namespace std;

const int mod = 1e9 + 7;
int t, n, k, a[maxl], p[maxl];
set<int> s;
int left[200], right[200], lt, rt;

int main() {

    scanf("%d", &t);
    while (t--) {
        s.clear();
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            p[i] = i;
        }
        sort(p + 1, p + n + 1, [&](int i, int j) { return a[i] > a[j]; });

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            lt = rt = 0;
            int pos = p[i];
            auto iter = s.lower_bound(pos);
            auto sv = iter;

            left[0] = pos;
            while (iter != s.begin()) {
                iter--;
                left[++lt] = *iter;
                if (lt >= k) break;
            }
            left[++lt] = 0;

            iter = sv;
            while (iter != s.end()) {
                right[++rt] = *iter;
                if (rt >= k) break;
                iter++;
            }
            for (int j = rt+1; j <= k; ++j)
                right[++rt] = n + 1;

            for (int j = 0; j < lt && j < k; ++j) {
                int num1 = left[j] - left[j+1];
                int num2 = right[k-j] - pos;
                int tmp = (ll)num1 * num2 % mod * a[pos] % mod;
                ans = (ans + tmp) % mod;
            }

            s.insert(pos);
        }
        printf("%d\n", ans);
    }

    return 0;
}

