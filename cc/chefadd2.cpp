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
const int maxl = 100010;
const int mod = 1e9 + 7;

int t, a, b, c;
int cnt[maxl], arr[50];

void calc(int n, int arr[]) {
    printf("%3d: ", n);
    for (int i = 0; i <= 31; i++) {
        if (n & (1 << i)) {
            arr[i] = 1;
        } else {
            arr[i] = 0;
        }
        printf("%d ", arr[i]);
    }
    puts("");
}

int main() {
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i < maxl; i++) {
        int n = i;
        while (n) {
            cnt[i]++;
            n -= (n & -n);
        }
    }
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &a, &b, &c);
        int ans = 0;
        calc(a, arr);
        calc(b, arr);
        puts("");
        for (int i = 1; i < c; i++) {
            int j = c - i;
            if (cnt[i] == cnt[a] && cnt[j] == cnt[b]) {
                ans++;
                calc(i, arr);
                calc(j, arr);
                puts("");
                if (ans > 10)
                    break;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}

