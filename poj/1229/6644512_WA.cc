#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#define maxl 500
#define INF 10000
using namespace std;

struct node
{
	int l, u, type;
	string str;
}
A[maxl], B[maxl];

char S[maxl], T[maxl];
int t1, t2;

int f[maxl][maxl];

void handle(char S[], node A[], int n, int& top)
{
	for(int i=0; i<n; ++i)
	{
		if(S[i] == '.') continue;
		int k = i;
		top++;
		A[top].str = "";
		while(k < n && S[k] != '.')
		{
			A[top].str += S[k];
			k++;
		}
		i = k;

		A[top].type = 2;

		if(A[top].str[0] == '*'){ A[top].l = 1; A[top].u = INF; }
		else if(A[top].str[0] == '?'){ A[top].l = 1; A[top].u = 3; }
		else if(A[top].str[0] == '!'){ A[top].l = 3; A[top].u = INF; }
		else{ A[top].l = A[top].u = A[top].str.length(); A[top].type = 1; }
	}
}

void init()
{
	scanf("%s%s", S, T);

	t1 = t2 = 0;

	handle(S, A, strlen(S), t1);
	handle(T, B, strlen(T), t2);

}

void solve()
{
	memset(f, 0, sizeof f);
	f[0][0] = 1;

	for(int i=1; i<=t1; ++i)
	{
		for(int j=1; j<=t2; ++j)
		{
			if(A[i].type == 1 && B[j].type == 1) f[i][j] = (A[i].str == B[j].str);
			else if(A[i].type == 2 && B[j].type == 1)
			{
				int lsum = 0, usum = 0;
				for(int k=j; k>=1; --k)
				{
					lsum += B[k].l; usum += B[k].u;
					if(A[i].l <= lsum && usum <= A[i].u && f[i-1][k-1]) f[i][j] = 1;
				}
			}
			else if(A[i].type == 1 && B[j].type == 2)
			{
				int lsum = 0, usum = 0;
				for(int k=i; k>=1; --k)
				{
					lsum += B[k].l; usum += B[k].u;
					if(B[j].l <= lsum && usum <= B[j].u && f[k-1][j-1]) f[i][j] = 1;
				}
			}
			else
			{
				int lsum = 0, usum = 0;
				for(int k=j; k>=1; --k)
				{
					lsum += B[k].l; usum += B[k].u;
					if(A[i].l <= lsum && usum <= A[i].u && f[i-1][k-1]) f[i][j] = 1;
				}

				lsum = 0, usum = 0;
				for(int k=i; k>=1; --k)
				{
					lsum += B[k].l; usum += B[k].u;
					if(B[j].l <= lsum && usum <= B[j].u && f[k-1][j-1]) f[i][j] = 1;
				}
			}
		}
	}

	if(f[t1][t2]) puts("YES");
	else puts("NO");
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}

