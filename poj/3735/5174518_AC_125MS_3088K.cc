#include <stdio.h>
#include <cstring>
#define sz 103
#define ll long long

ll A[sz][sz];
long long B[sz][sz];
ll I[sz][sz];
int n, m, k;

void matrix(ll C[][sz], ll A[][sz], ll B[][sz])
{
    for(int i=1; i<n+2; ++i) for(int j=1; j<n+2; ++j) C[i][j] = 0;
	for(int i=1; i<n+2; ++i)
	{
	    for(int k=1; k<n+2; ++k)
	    {
	        if(A[i][k]==0) continue;
		    for(int j=1; j<n+2; ++j)
		    {
			    
			    	C[i][j] += (ll)A[i][k] * B[k][j];
		    }
		}
	}
}

void pow(long long B[][sz], int n)
{
	if(n==0)
	{
		return;
	}
	ll tmp[sz][sz];
	pow(B, n/2);
	matrix(tmp, B, B);
	if(n & 1) matrix(B, tmp, A);
	else matrix(B, I, tmp);
}

void make_matrix()
{
	char s[2];
	int a, b, c;
	for(int x=0; x<k; ++x)
	{
		scanf("%s", s);
		if(s[0]=='g')
		{
			scanf("%d", &c);
			A[n+1][c]++;
		}
		else if(s[0]=='e')
		{
			scanf("%d", &c);
			for(int i=1; i<=n+1; ++i) A[i][c] = 0;
		}
		else if(s[0]=='s')
		{
			scanf("%d%d", &a, &b);
			for(int i=1; i<=n+1; ++i)
			{
				int tmp = A[i][a]; A[i][a] = A[i][b]; A[i][b] = tmp;
			}
		}
	}
}

void solve()
{
	memset(I, 0, sizeof I);
	memset(A, 0, sizeof A);
	memset(B, 0, sizeof B);
	for(int i=0; i<n+2; ++i){ I[i][i] = 1; A[i][i] = 1; B[i][i] = 1; }

	
	make_matrix();

	pow(B, m);

	for(int i=1; i<n; ++i) printf("%I64d ", B[n+1][i]);
	printf("%I64d\n", B[n+1][n]);
}

int main()
{
	while(scanf("%d%d%d", &n, &m, &k) && n)
	{
		solve();
	}
	return 0;
}