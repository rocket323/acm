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
const int maxl = 1e5 + 10;

int n, a[maxl];

int main() {
    scanf("%d", &n);
    int p = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (i == p + 1 && a[i] > a[p]) {
            p = i;
        }
    }
    printf("%d\n", a[p]);
    return 0;
}
