#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#define INF 0x3f3f3f3f
#define min(a,b) ((a<b)?a:b)

int A[300][300], b[300], n, ret[300];
char S[16][16];

void go(int i, int j, int r)
{
	int c = i * n + j;
	A[r][c] = 1;
}

void out()
{
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j) printf("%d ", A[i][j]);
		puts("");
	}
}

void init()
{
	scanf("%d", &n);
	for(int i=0; i<n; ++i)
	{
		scanf("%s", S[i]);
		for(int j=0; j<n; ++j) b[i*n+j] = (S[i][j] == 'w');
	}

	memset(A, 0, sizeof A);
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			int k = i * n + j;
			go(i, j, k);
			if(i > 0) go(i-1, j, k);
			if(j > 0) go(i, j-1, k);
			if(i < n-1) go(i+1, j, k);
			if(j < n-1) go(i, j+1, k);
		}
	}
	n *= n;
}

int sqrt(int n)
{
	for(int i=0; i<n; ++i) if(i * i == n) return i;
	return -1;
}

void guass()
{
	int  k, tmp, rec = n;

	//out();

	for(int i=0; i<n; ++i)
	{
		k = -1;
		for(int j=i; j<n; ++j)
			if(A[j][i]) k = j;

		if(k == -1){ rec = i; break; }

		for(int j=i; j<n; ++j)
		{
			tmp=A[i][j]; A[i][j]=A[k][j]; A[k][j]=tmp;
		}
		tmp = b[i]; b[i] = b[k]; b[k] = tmp;

		for(int j=i+1; j<n; ++j)
		{
			if(A[j][i])
			{
				for(int k=i; k<n; ++k) A[j][k] ^= A[i][k];
				b[j] ^= b[i];
			}
		}
	}

	//printf("%d\n", rec);


	//out();

	int ans = INF;
	for(int x=0; x<(1<<(n-rec)); ++x)
	{
		int tmp = 0;
		for(int j=rec; j<n; ++j){ ret[j] = x & (1<<(j-rec)); tmp += ret[j]; }
		for(int i=rec-1; i>=0; --i)
		{
			ret[i] = b[i];
			for(int j=n-1; j>i; --j) ret[i] ^= (ret[j] & A[i][j]);
			tmp += ret[i];
		}
		ans = min(ans, tmp);
	}

	/*
	for(int i=0; i<n; ++i)
	{
		printf("%d %d %d\n", i/sqrt(n), i%sqrt(n), b[i]);
	}
	*/

	printf("%d\n", ans);
}

void solve()
{
	guass();
}

int main()
{
	int t, tc = 0;
	scanf("%d", &t);
	while(t--)
	{
		init();
		solve();
	}
	return 0;
}
