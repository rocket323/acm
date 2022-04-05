#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream>
#define maxl 500
#define INF 1000000
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
		else if(A[top].str[0] == '!')
		{
			for(int i=0; i<3; ++i)
			{
				A[top+i].l = 1; A[top+i].u = INF;
				A[top+i].str = "*";
				A[top+i].type = 2;
			}
			top = top + 2;
		}
		else{ A[top].l = A[top].u = 1; A[top].type = 1; }
	}
}

void init()
{
	scanf("%s%s", S, T);

	t1 = t2 = 0;

	handle(S, A, strlen(S), t1);
	handle(T, B, strlen(T), t2);

	/*
	for(int i=1; i<=t1; ++i) cout << A[i].str << ' ' << A[i].l << ' ' << A[i].u << ' ' << A[i].type << endl;
	for(int i=1; i<=t2; ++i) cout << B[i].str << ' ' << B[i].l << ' ' << B[i].u << ' ' << B[i].type << endl;
	*/
}

int in(int x, int a, int b)
{
	return (a <= x && x <= b);
}

void solve()
{
	memset(f, 0, sizeof f);
	f[0][0] = 1;

	for(int i=1; i<=t1; ++i)
	{
		for(int j=1; j<=t2; ++j)
		{
			if(A[i].type == 1 && B[j].type == 1) f[i][j] = (A[i].str == B[j].str && f[i-1][j-1]);
			else if(A[i].type == 2 && B[j].type == 1)
			{
				int lsum = 0, usum = 0;
				for(int k=j; k>=1; --k)
				{
					lsum += B[k].l; usum += B[k].u;
					if(usum > INF) usum = INF;
					if((in(lsum, A[i].l, A[i].u) || in(usum, A[i].l, A[i].u)) && f[i-1][k-1]) f[i][j] = 1;
				}
			}
			else if(A[i].type == 1 && B[j].type == 2)
			{
				int lsum = 0, usum = 0;
				for(int k=i; k>=1; --k)
				{
					lsum += A[k].l; usum += A[k].u;
					if(usum > INF) usum = INF;
					if((in(lsum, B[j].l, B[j].u) || in(usum, B[j].l, B[j].u)) && f[k-1][j-1])
					{
						f[i][j] = 1;
					}
				}
			}
			else
			{
				int lsum = 0, usum = 0;
				for(int k=j; k>=1; --k)
				{
					lsum += B[k].l; usum += B[k].u;
					if(usum > INF) usum = INF;
					if((in(lsum, A[i].l, A[i].u) || in(usum, A[i].l, A[i].u)) && f[i-1][k-1]) f[i][j] = 1;
				}

				lsum = 0, usum = 0;
				for(int k=i; k>=1; --k)
				{
					lsum += A[k].l; usum += A[k].u;
					if(usum > INF) usum = INF;
					if((in(lsum, B[j].l, B[j].u) || in(usum, B[j].l, B[j].u)) && f[k-1][j-1]) f[i][j] = 1;
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

