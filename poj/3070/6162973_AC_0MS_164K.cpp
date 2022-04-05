#include <stdio.h>
#include <cstring>
#define mod 10000

int A[2][2] = {1, 1, 1, 0};
int B[2][2], t[2][2], n, tmp[2][2];

void matrix(int C[][2], int A[][2], int B[][2])
{
	for(int i=0; i<2; ++i)
	{
		for(int j=0; j<2; ++j)
		{
			C[i][j] = 0;
			for(int k=0; k<2; ++k) C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
		}
	}
}

int solve(int n)
{
	if(n == 0) return 0;
	n--;

	memset(B, 0, sizeof B);
	B[0][0] = B[1][1] = 1;
	memcpy(t, A, sizeof A);

	while(n)
	{
		if(n & 1)
		{
			matrix(tmp, B, t);
			memcpy(B, tmp, sizeof tmp);
		}

		matrix(tmp, t, t);
		memcpy(t, tmp, sizeof tmp);
		n /= 2;
	}

	return B[0][0];
}

int main()
{
	while(scanf("%d", &n), n != -1)
	{
		printf("%d\n", solve(n));
	}
	return 0;
}
