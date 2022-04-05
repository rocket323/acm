#include <stdio.h>
#include <cstring>
#define mod 2005

int A[4][4]={{1,1,0,0}, {0,0,1,1}, {1,0,0,0}, {0,0,1,0}};
int I[4][4]={{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}};
int B[4][4], tmp[4][4], t[4][4];

void matrix(int C[][4], int A[][4], int B[][4])
{
	for(int i=0; i<4; ++i)
	{
		for(int j=0; j<4; ++j)
		{
			C[i][j] = 0;
			for(int k=0; k<4; ++k) C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
		}
	}
}

int solve(int n)
{
	if(n < 2) return 2;

	n -= 2;
	memcpy(B, I, sizeof I);
	memcpy(t, A, sizeof A);
	while(n)
	{
		if(n & 1)
		{
			matrix(tmp, B, t);
			memcpy(B, tmp, sizeof tmp);
		}

		n /= 2;

		matrix(tmp, t, t);
		memcpy(t, tmp, sizeof tmp);
	}

	int ans = 0;
	for(int i=0; i<4; ++i)
	{
		for(int j=0; j<4; ++j) ans = (ans + B[i][j]) % mod;
	}
	return ans;
}

int main()
{
	int n;
	while(scanf("%d", &n) != EOF)
	{
		printf("%d\n", solve(n));
	}
	return 0;
}
