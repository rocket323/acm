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

int a[maxl], h;

int main() {
    for (int i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &h);
    int ans = 0;
    for (int i = 0; i < 10; i++) {
        if (a[i] <= h + 30)
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}
