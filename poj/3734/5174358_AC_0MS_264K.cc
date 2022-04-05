#include <stdio.h>
#include <cstring>
#define mod 10007

int A[4][4]={2, 1, 1, 0,
			 1, 2, 0, 1,
			 1, 0, 2, 1,
			 0, 1, 1, 2};
int B[4][4];
int I[4][4];
int n;

void matrix(int C[][4], int A[][4], int B[][4])
{
	for(int i=0; i<4; ++i)
	{
		for(int j=0; j<4; ++j)
		{
			C[i][j] = 0;
			for(int k=0; k<4; ++k)
				C[i][j] = (A[i][k] * B[k][j] + C[i][j]) % mod;
		}
	}
}

void pow(int B[][4], int n)
{
	if(n==0)
	{
		memcpy(B, I, sizeof I);
		return;
	}
	int tmp[4][4];
	pow(B, n/2);
	matrix(tmp, B, B);
	if(n & 1) matrix(B, tmp, A);
	else matrix(B, tmp, I);
}

int solve(int n)
{
	memset(I, 0, sizeof I);
	for(int i=0; i<4; ++i) I[i][i] = 1;
	pow(B, n);
	return B[0][0];
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", solve(n));
	}
	return 0;
}