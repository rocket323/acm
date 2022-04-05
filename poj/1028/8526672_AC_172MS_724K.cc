#include <stdio.h>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int fs_t, bs_t;
string fs[1000], bs[1000], cur, cmd, url;

int main()
{
	fs_t = bs_t = 0;
	cur = "http://www.acm.org/";
	while(cin >> cmd) {
		if(cmd == "QUIT") break;
		if(cmd == "VISIT") {
			cin >> url;
			bs[bs_t++] = cur;
			cur = url;
			cout << url << endl;
			fs_t = 0;
		}
		else if(cmd == "BACK") {
			if(bs_t == 0) {
				puts("Ignored");
			}
			else {
				fs[fs_t++] = cur;
				cur = bs[--bs_t];
				cout << cur << endl;
			}
		}
		else if(cmd == "FORWARD") {
			if(fs_t == 0) {
				puts("Ignored");
			}
			else {
				bs[bs_t++] = cur;
				cur = fs[--fs_t];
				cout << cur << endl;
			}
		}
	}
	return 0;
}
