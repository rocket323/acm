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

ll n, d, t;
int f[10];
ll curN, curCnt;
ll ansN, ansCnt;

void calc(ll &n, ll &cnt) {
    while (n >= 10) {
        cnt++;
        ll tmp = n;
        n = 0;
        while (tmp > 0) {
            n += tmp % 10;
            tmp /= 10;
        }
    }
}

void update() {
    if (ansN == -1 || curN < ansN) {
        ansN = curN, ansCnt = curCnt;
    } else if (curN == ansN && curCnt < ansCnt) {
        ansN = curN, ansCnt = curCnt;
    }
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> d;
        ansN = -1, ansCnt = 0;

        for (ll i = 0; i < 1000000; i++) {
            curCnt = i;
            curN = n + i * d;
            calc(curN, curCnt);
            update();
        }
        cout << ansN << ' ' << ansCnt << endl;
    }

    return 0;
}

