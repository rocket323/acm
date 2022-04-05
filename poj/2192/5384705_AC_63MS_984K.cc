#include <stdio.h>
#include <cstring>
#define MaxL 401

int l1, l2, n, f[MaxL][MaxL];
char A[MaxL], B[MaxL], C[MaxL];

void init()
{
	scanf("%s%s%s", A, B, C);
	l1 = strlen(A);
	l2 = strlen(B);
	n = strlen(C);
}

int solve()
{
	memset(f, 0, sizeof f);
	f[0][0] = true;

	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<=l1; ++j)
		{
			if(!f[i][j]) continue;
			if(j < l1 && A[j] == C[i]) f[i+1][j+1] = 1;
			if(B[i-j] == C[i]) f[i+1][j] = 1;
		}
	}
	for(int j=0; j<=l1; ++j)
		if(f[n][j]) return 1;
	return 0;
}

int main()
{
	int t;
	scanf("%d", &t);
	for(int i=1; i<=t; ++i)
	{
		init();
		int k = solve();
		printf("Data set %d: ", i);
		if(k) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}