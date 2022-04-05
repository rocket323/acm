#include <stdio.h>
#include <cstring>

char S[10010][80], T[10010];
int p[10010], n, m;

int gcd(int a, int b)
{
	if(b==0) return a;
	else return gcd(b, a % b);
}

int lcm(int a, int b)
{
	return a / gcd(a, b) * b;
}

int kmp(char S[], int n)
{
	p[0] = -1;
	int j = -1;

	for(int i=1; i<n; ++i)
	{
		while(j>-1 && S[j+1]!=S[i]) j = p[j];
		if(S[j+1]==S[i]) j++;
		p[i] = j;
	}
	return n - 1 - p[n - 1];
}

void solve()
{
	int h = 1, w = 1;

	for(int i=0; i<n; ++i)
	{
		int k = kmp(S[i], strlen(S[i]));
		w = lcm(w, k);
	}

	for(int i=0; i<m; ++i)
	{
		for(int j=0; j<n; ++j) T[j] = S[j][i];
		int k = kmp(T, n);
		h = lcm(h, k);
	}

	printf("%d\n", h * w);
}

int main()
{
	while(scanf("%d%d", &n, &m) != EOF)
	{
		for(int i=0; i<n; ++i) scanf("%s", S[i]);
		solve();
	}
	return 0;
}

