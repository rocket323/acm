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
        a1 = 0; a2 = ch - 'A';
    } else {
        a1 = 1; a2 = ch - 'A';
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
        scanf("%s", s);
        n = strlen(s);
        sort(s, s + n, cmp);
        do {
            printf("%s\n", s);
        } while (next_permutation(s, s + n, cmp));
    }

    return 0;
}
