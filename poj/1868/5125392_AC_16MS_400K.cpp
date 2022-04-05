#include <stdio.h>
#include <sstream>
#include <iostream>
#include <cstring>
#define MaxL 10001
using namespace std;

int n, a[MaxL];
char S[10];
int l[MaxL], r[MaxL];

int check(char S[])
{
	istringstream in(S);
	in >> n;
	return n;
}

void init()
{
	memset(l, 0, sizeof l);
	memset(r, 0, sizeof r);
	for(int i=0; i<n; ++i)
	{
		scanf("%d", &a[i]);
		r[a[i]]++;
	}
}

void solve()
{
	for(int i=0; i<n; ++i)
	{
		r[a[i]]--;
		for(int j=0; j<i; ++j)
		{
			if(2*a[i]>=a[j] && r[2*a[i]-a[j]])
			{
				printf("no\n");
				return;
			}
		}
	}
	printf("yes\n");
}

int main()
{
	while(cin>>S, check(S))
	{
		init();
		solve();
	}
	return 0;
}