#include <iostream>
#define MaxL 501
#define ll long long
#define mod 20090305 
using namespace std;

int d[3];
char S[MaxL];
int f[2][MaxL][MaxL], now, pre;
int pa[MaxL], pb[MaxL], pc[MaxL], a, b, c;

void init()
{
	memset(d, 0, sizeof d);
	for(int i=0; i<3; ++i) scanf("%d", &d[i]);
	getchar();
	gets(S);
	int len = strlen(S);
	a = b = c = 0;
	for(int i=0; i<len; ++i)
	{
		if(S[i]=='A') pa[++a] = i + 1;
		if(S[i]=='B') pb[++b] = i + 1;
		if(S[i]=='C') pc[++c] = i + 1;
	}
}

int Min(int a, int b){ return(a<b)?a:b; }

void solve()
{
	memset(f, 0, sizeof f);
	f[now][0][0] = 1;
	int len = strlen(S);
	now = 0;
	for(int i=0; i<len; ++i)
	{
		now = (now + 1) % 2;
		pre = (now + 1) % 2;
		memset(f[now], 0, sizeof f[now]);
		for(int j=0; j<=a; ++j)
		{
			for(int k=0; k<=Min(i-j, b); ++k)
			{	
				if(f[pre][j][k]==0) continue;
				f[now][j][k] = (f[now][j][k] + ((ll)(abs(i+1-pc[i+1-j-k])<=d[2]) * f[pre][j][k])%mod ) % mod;
				f[now][j][k+1] = (f[now][j][k+1] + ((ll)(abs(i+1-pb[k+1])<=d[1]) * f[pre][j][k]) % mod ) % mod;
				f[now][j+1][k] = (f[now][j+1][k] +  ((ll)(abs(i+1-pa[j+1])<=d[0]) * f[pre][j][k]) % mod ) % mod ;
			}
		}
	}
	printf("%d\n", f[now][a][b]);
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
