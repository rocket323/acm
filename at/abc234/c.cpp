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
using ll = unsigned  long long;

const int inf = 0x3f3f3f3f;
const int maxl = 1e5 + 10;

ll k;
int ans[maxl];

int main() {
    cin >> k;
    k++;
    for (int i = 63; i >= 1; i--) {
        ll x = (((ll)1) << i);
        if (x >= k) {
            ans[i] = 0;
        } else {
            ans[i] = 2;
            k -= x;
        }
    }
    if (k > 1)
        ans[0] = 2;

    int i = 63;
    while (ans[i] == 0 && i > 0)
        i--;
    for (int j = i; j >= 0; j--)
        printf("%d", ans[j]);
    puts("");
    
    return 0;
}

