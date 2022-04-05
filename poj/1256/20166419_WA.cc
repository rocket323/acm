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

int t, n;
char s[20];

void getRange(char ch, int &a1, int &a2) {
    if (ch >= 'A' && ch <= 'Z') {
        a1 = ch - 'A'; a2 = 0;
    } else {
        a1 = ch - 'A'; a2 = 1;
    }
}

bool cmp(char a, char b) {
    int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
    getRange(a, a1, a2);
    getRange(b, b1, b2);
    return a1 < b1 || (a1 == b1 && a2 < b2);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        memset(s, 0, sizeof s);
        scanf("%s", s);
        n = strlen(s);
        sort(s, s + n, cmp);
        do {
            printf("%s\n", s);
        } while (next_permutation(s, s + n, cmp));
    }

    return 0;
}
