#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
#define min(a,b) ((a<b)?a:b)
#define max(a,b) ((a>b)?a:b)

struct node
{
	int a, b;
	char str[100];
}list[2][100000];

int f[100][100], top[2];
char s[100], t[100];

bool cmp(node A, node B)
{
	return strcmp(A.str, B.str) < 0;
}

void solve()
{
	int n = strlen(s), m = strlen(t);

	int ans = 0;
	for(int i=0; i<n; ++i){ ans = max(ans, (f[i][0] = (s[i] == t[0]))); }
	for(int i=0; i<m; ++i){ ans = max(ans, (f[0][i] = (s[0] == t[i]))); }

	for(int i=1; i<n; ++i)
	{
		for(int j=1; j<m; ++j)
		{
			f[i][j] = 0;
			if(s[i] == t[j])
			{
				for(int a=0; a<i; ++a)
					for(int b=0; b<j; ++b)
						f[i][j] = max(f[i][j], f[a][b] + 1);
			}
			ans = max(ans, f[i][j]);
		}
	}


	top[0] = 1;
	list[0][0].a = list[0][0].b = -1;
	strcpy(list[0][0].str, "");

	for(int i=1; i<=ans; ++i)
	{
		top[i&1] = 0;
		for(int a=0; a<n; ++a)
		{
			for(int b=0; b<m; ++b)
			{
				if(f[a][b] != i) continue;

				for(int k=0; k<top[(i+1)&1]; ++k)
				{
					if(list[(i+1)&1][k].a >= a || list[(i+1)&1][k].b >= b) continue;

					int x = top[i&1]++;
					list[i&1][x].a = a;
					list[i&1][x].b = b;
					for(int p=0; p<i-1; ++p) list[i&1][x].str[p] = list[(i+1)&1][k].str[p];
					list[i&1][x].str[i-1] = s[a];
					if(x >= 70000) while(1);
				}
			}
		}
	}
	sort(list[ans&1], list[ans&1] + top[ans&1], cmp);

	for(int i=0; i<top[ans&1]; ++i)
		list[ans&1][i].str[ans] = 0;

	puts(list[ans&1][0].str);

	int idx = ans & 1;
	for(int i=1; i<top[ans&1]; ++i)
	{
		if(strcmp(list[idx][i].str, list[idx][i-1].str) == 0) continue;
		puts(list[idx][i].str);
	}
}

int main()
{
	scanf("%s%s", s, t);
	solve();
	return 0;
}

