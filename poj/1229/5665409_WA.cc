#include <stdio.h>
#include <cstring>
#define MaxL 260
#define max(a,b) ((a>b)?a:b)

char S1[MaxL], S2[MaxL];
char A1[MaxL][MaxL], A2[MaxL][MaxL];
int t1, t2, MM;
int f[MaxL][MaxL], n1, n2;

void go(char S[], char A[][MaxL], int& t)
{
	t = 1;
	int l = 0;
	for(int i=0; S[i]; ++i)
	{
		if(S[i]=='.')
		{
			A[t][l] = 0;
			t++;
			l = 0;
		}
		else
		{
			A[t][l++] = S[i];
		}
	}
	A[t][l] = 0;
}

void init()
{
	scanf("%s%s", S1, S2);
	go(S1, A1, t1);
	go(S2, A2, t2);

	MM = max(t1, t2) + 5;

	//puts(S1);
	//puts(S2);
/*
	for(int i=1; i<=t2; ++i)
	{
		printf("%s\n", A2[i]);
	}
*/
}

bool letter(char ch)
{
	return ( (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') );
}

int low(char ch)
{
	if(ch=='?') return 1;
	if(ch=='*') return 1;
	if(ch=='!') return 3;
}

int up(char ch)
{
	if(ch=='?') return 3;
	if(ch=='*') return MM;
	if(ch=='!') return MM;
}

int dp(int r, int c)
{
	if(f[r][c] != -1) return f[r][c];
	if(r < 0 || c < 0) return 0;
	if((r<=0 && c>0) || (r>0 && c<=0)) return 0;

	//printf("%d %d %s %s\n", r, c, A1[r], A2[c]);

	int ans = 0;
	if(letter(A1[r][0]) && letter(A2[c][0]))
	{
		ans = (strcmp(A1[r], A2[c]) == 0 && dp(r-1, c-1));
	}
	else if(letter(A1[r][0]))
	{
		int l = low(A2[c][0]), u = up(A2[c][0]);
		for(int i=l; i<=u; ++i)
		{
			if(dp(r-i, c-1))
			{
				ans = 1;
				break;
			}
		}
	}
	else if(letter(A2[c][0]))
	{
		int l = low(A1[r][0]), u = up(A1[r][0]);
		for(int i=l; i<=u; ++i)
		{
			if(dp(r-1, c-i))
			{
				ans = 1;
				break;
			}
		}
	}
	else
	{
		int l1 = low(A1[r][0]), u1 = up(A1[r][0]);
		int l2 = low(A2[c][0]), u2 = up(A2[c][0]);

		for(int i=0; i<=(u1-l2); ++i)
		{
			if(dp(r-1, c-1-i))
			{
				ans = 1;
				break;
			}
		}
		
		for(int i=0; i<=(u2-l1) && !ans; ++i)
		{
			if(dp(r-1-i, c-1))
			{
				ans = 1;
				break;
			}
		}
	}
	return f[r][c] = ans;
}

void solve()
{
	memset(f, -1, sizeof f);
	f[0][0] = 1;

	int flag = dp(t1, t2);

	if(flag) puts("YES");
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

