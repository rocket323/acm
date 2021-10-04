#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxl = 1e5 + 10;
long long a, b;

int main() {
    cin >> a >> b;
    long long ans = 1;
    for (int i = 0; i < a - b; i++)
        ans = ans * 32;
    cout << ans << endl;
    return 0;
}

