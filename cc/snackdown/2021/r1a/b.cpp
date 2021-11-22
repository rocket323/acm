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

int t, x, k;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &x, &k);
        cout << x * 2 << ' ' << (ll)(x * k - 1) * x * k << endl;
    }
    return 0;
}
