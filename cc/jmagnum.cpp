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

int t, l, r;
int a[maxl], s[maxl];

int main() {
    scanf("%d", &t);

    memset(s, 0, sizeof s);
    memset(a, 0, sizeof a);
    for (int i = 2; i < maxl; ++i) {
        if (a[i] > 0) continue;
        int s = 0, n = i;
        while (n) {
            s += n % 10;
            n /= 10;
        }
        for (int j = i; j < maxl; j += i)
            a[j] += s;
    }
    for (int i = 1; i < maxl; ++i) {
        s[i] = s[i - 1] + a[i];
    }

    while (t--) {
        scanf("%d%d", &l, &r);
        printf("%d\n", s[r] - s[l - 1]);
    }

    return 0;
}

