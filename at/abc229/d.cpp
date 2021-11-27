#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

char s[maxl];
int n, k, sum[maxl], ans;

int getSum(int i, int j) {
    int ans = sum[j];
    if (i > 0)
        ans -= sum[i - 1];
    return ans;
}

int main() {
    scanf("%s", s);
    scanf("%d", &k);
    n = strlen(s);
    for (int i = 0; i < n; i++) {
        int x = (s[i] == '.');
        sum[i] = x;
        if (i > 0)
            sum[i] += sum[i-1];
    }
    int p = 0;
    ans = 0;
    for (int i = 0; i < n; i++) {
        while (p < i && getSum(p, i) > k)
            p++;
        if (getSum(p, i) <= k)
            ans = max(ans, i - p + 1);
    }
    printf("%d\n", ans);

    return 0;
}

