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

string s;

int gao() {
    if (s == "Monday")
        return 5;
    if (s == "Tuesday")
        return 4;
    if (s == "Wednesday")
        return 3;
    if (s == "Thursday")
        return 2;
    if (s == "Friday")
        return 1;
    return 0;
}

int main() {
    cin >> s;
    cout << gao() << endl;
    return 0;
}