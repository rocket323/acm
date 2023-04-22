#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;
using ll = long long;

const int inf = 0x3f3f3f3f;
const int maxl = 200;

void test1() {
    int n = 200;
    int m = 20;
    printf("%d\n", m);
    for (int i = 0; i < n; i++) {
        char ch = rand() % 10 + 'A';
        printf("%c", ch);
    }
    puts("");
}

void test2() {
    int n = 200;
    int m = 20;
    printf("%d\n", m);
    for (int i = 0; i < n; i++) {
        char ch = i % 2 + 'A';
        printf("%c", ch);
    }
    puts("");
}

int main() {
    srand(time(0));
    test1();
    test2();
    return 0;
}