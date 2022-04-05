#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

struct node
{
	int s, t;
}E[81];

int A[81][81], B[81][81], C[81][81], n;

bool cmp(node A, node B){ return A.t < B.t; }

void make_Gra()
{
	memset(A, 0, sizeof A);
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			if(i==j) continue;
			if(E[j].s >= E[i].t) A[i][j] = 1;
		}
	}
}

void matrix(int C[][81], int A[][81], int B[][81])
{
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			C[i][j] = 0;
			for(int k=0; k<n; ++k) C[i][j] += A[i][k] * B[k][j];
		}
	}
}

void out(int A[][81])
{
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j) printf("%d ", A[i][j]);
		printf("\n");
	}
	puts("");
}

void solve()
{
	int len=0, t = -1000000, ans;
	sort(E, E+n, cmp);
	for(int i=0; i<n; ++i)
	{
		if(E[i].s >= t)
		{
			len++;
			t = E[i].t;
		}
	}
	make_Gra();

	memset(B, 0, sizeof B);
	for(int i=0; i<n; ++i) B[i][i] = 1;

	for(int i=1; i<len; ++i)
	{
		matrix(C, B, A);
		memcpy(B, C, sizeof C);
	}

	ans = 0;
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j) ans += C[i][j];
	}
	if(len==1) ans = 1;
	printf("%d %d\n", n - len, ans);
}

int main()
{
	while(scanf("%d", &n)!=EOF)
	{
		for(int i=0; i<n; ++i)
		{
			scanf("%d%d", &E[i].s, &E[i].t);
			if(E[i].s > E[i].t) swap(E[i].s, E[i].t);
		}
		solve();
	}
	return 0;
}