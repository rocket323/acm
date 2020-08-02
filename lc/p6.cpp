#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Node {
    int r;
    int c;
    char ch;
};

bool cmp(const Node &a, const Node &b) {
    return (a.r < b.r || (a.r == b.r && a.c < b.c)); 
}

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) {
            return s;
        }
        vector<Node> v;
        int n = s.length();
        int r = 1, c = 1, dr = 1, dc = 0;
        for (int i = 0; i < n; i++) {
            Node nd = {r, c, s[i]};
            v.push_back(nd);
            if (r == numRows) {
                dr = -1;
                dc = 1;
                r--;
                c++;
            } else if (r == 1) {
                dr = 1;
                dc = 0;
                r++;
            } else {
                r += dr;
                c += dc;
            }
        }

        sort(v.begin(), v.end(), cmp);
        string ans;
        for (auto &c : v) {
            ans += c.ch;
        }

        return ans;
    }
};

int main() {
    Solution sol;
    std::string s = "ABCDEFGHIJ";
    int n = 4;
    cout << sol.convert(s, n) << endl;

    return 0;
}
