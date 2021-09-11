#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int maxl = 1e5 + 10;
int a[26];

int main() {
    for (int i = 0; i < 26; i++) {
        scanf("%d", &a[i]);
        printf("%c", 'a' + a[i] - 1);
    }
    return 0;
}

