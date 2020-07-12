#include <stdio.h>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

typedef long long ll;
const int maxl = 1000010;
const int mod = 1e9 + 7;

int t, n;
ll a[maxl];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);

        ll sum = (1LL << 32) - 100;
        ll m = n - 2;
        for (int i = 2; i < n; ++i) {
            a[i] = sum / m;
        }
        sum -= sum / m * m;
        for (int i = 2; i < n; ++i) {
            if (sum > 0) {
                a[i]++;
                sum--;
            }
        }
        a[0] = 20;
        a[1] = 50;

        for (int i = 0; i < n; ++i) {
            cout << a[i];
            if (i == n - 1) cout << endl;
            else cout << ' ';
            // if (a[i] <= 0 || a[i] > 100000)
                // printf("%d %lld\n", i, a[i]);
            assert(a[i] >= 1 && a[i] <= 100000);
        }
    }

    return 0;
}

