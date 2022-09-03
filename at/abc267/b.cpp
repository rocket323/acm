#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 2e5 + 10;

int L[20] = {0, 4, 3, 5, 2, 4, 6, 1, 3, 5, 7};
int c[20];
char s[20];

string gao() {
    if (s[0] == '1')
        return "No";

    for (int i = 0; i < 10; i++) {
        int x = s[i] - '0';
        c[L[i + 1]] += x;
    }

    // for (int i = 1; i <= 7; i++)
    //     cout << c[i] << ' ';
    // cout << endl;

    for (int i = 1; i <= 7; i++) {
        for (int j = i + 1; j <= 7; j++) {
            if (c[i] == 0 || c[j] == 0)
                continue;
            for (int k = i + 1; k < j; k++) {
                if (c[k] == 0)
                    return "Yes";
            }
        }
    }
    return "No";
}

int main() {
    scanf("%s", s);
    cout << gao() << endl;
    return 0;
}