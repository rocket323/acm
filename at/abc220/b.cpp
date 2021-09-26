#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

const int maxl = 1e5 + 10;
int k, a, b;
ll n;
char s[100], t[100];

int gao(char s[]) {
    int ans = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        ans = ans * k + s[i] - '0';
    }
    return ans;
}

int main() {
    scanf("%d", &k);
    scanf("%s%s", s, t);

    a = gao(s);
    b = gao(t);
    cout << (ll)a * b << endl;

    return 0;
}

