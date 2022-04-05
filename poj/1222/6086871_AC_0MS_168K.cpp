#include <stdio.h>
#include <cstring>
#include <stdlib.h>

int A[30][30], b[30];

void go(int i, int j, int r)
{
	int c = i * 6 + j;
	A[r][c] = 1;
}

void init()
{
	for(int i=0; i<5; ++i)
		for(int j=0; j<6; ++j) scanf("%d", &b[i*6+j]);

	memset(A, 0, sizeof A);
	for(int i=0; i<5; ++i)
	{
		for(int j=0; j<6; ++j)
		{
			int k = i * 6 + j;
			go(i, j, k);
			if(i > 0) go(i-1, j, k);
			if(j > 0) go(i, j-1, k);
			if(i < 4) go(i+1, j, k);
			if(j < 5) go(i, j+1, k);
		}
	}
}

void guass()
{
	int n = 30, k, tmp;
	for(int i=0; i<n; ++i)
	{
		k = i;
		for(int j=i; j<n; ++j)
			if(A[j][i]) k = j;
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

	for(int i=n-2; i>=0; --i)
	{
		for(int j=n-1; j>i; --j) b[i] ^= (b[j] & A[i][j]);
	}

	for(int i=0; i<5; ++i)
	{
		for(int j=0; j<6; ++j)
		{
			printf("%d%c", b[i*6+j], j==5 ? '\n' : ' ');
		}
	}
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
		printf("PUZZLE #%d\n", ++tc);
		init();
		solve();
	}
	return 0;
}

