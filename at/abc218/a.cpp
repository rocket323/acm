#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxl = 1e5 + 10;
int n;
char s[10];

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    puts(s[n - 1] == 'o' ? "Yes" : "No");

    return 0;
}
