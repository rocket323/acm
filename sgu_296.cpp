#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#define maxl 1010

char s[maxl];
int n, k, m;

string process()
{
	n = strlen(s);
	m = n - k;
	if(m <= 0) return "";

	ostringstream oss;
	int p = 0;
	int num = m;
	for(int i=0; i<num; ++i)
	{
		int idx = -1;
		char ch = 0;
		for(int j=p; n-j>=m; ++j)
		{
			if(s[j] > ch)
			{
				idx = j;
				ch = s[j];
			}
		}
		oss << ch;
		p = idx + 1;
		m--;
	}

	return oss.str();
}

int main()
{
	scanf("%s%d", s, &k);

	cout << process() << endl;

	return 0;
}

