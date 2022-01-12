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
const int maxl = 5e5 + 10;

int n, k, a[maxl];
set<int> s;

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        s.insert(a[i]);
        if (i > k) {
            s.erase(s.begin());
        }
        if (i >= k) {
            printf("%d\n", *s.begin());
        }
    }

    return 0;
}
