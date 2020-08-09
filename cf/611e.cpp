#include <stdio.h>
#include <cstring>
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;
#define maxl 200010

int n, a[maxl], t[maxl];
set<int> s;
int sum;

int Process()
{
	for(int i=0; i<n; ++i) if(t[i] > sum) return -1;

	sort(a, a + 3);
	while(s.size() > 0)
	{
		break;
	}
	return -1;
}

int main()
{
	scanf("%d", &n);
	sum = 0;
	for(int i=0; i<3; ++i)
	{
		scanf("%d", &a[i]);
		sum += a[i];
	}

	for(int i=0; i<n; ++i)
	{
		scanf("%d", &t[i]);
		s.insert(t[i]);
	}

	int ans = Process();
	printf("%d\n", ans);

	return 0;
}

