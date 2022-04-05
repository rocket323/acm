#include <iostream>
#define MaxL 501
#define ll long long
#define mod 20090305 
using namespace std;

int d[3];
char S[MaxL];
int f[MaxL][MaxL], f1[MaxL][MaxL];
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

void solve()
{
	memset(f, 0, sizeof f);
	memset(f1, 0, sizeof f1);
	f1[0][0] = 1;
	int len = strlen(S);
	for(int i=0; i<len; ++i)
	{
		memset(f, 0, sizeof f);
		for(int j=0; j<=i; ++j)
		{
			for(int k=0; k<=i-j; ++k)
			{	
				if(f1[j][k]==0) continue;
				f[j][k] = (f[j][k] + ((ll)(abs(i+1-pc[i+1-j-k])<=d[2]) * f1[j][k])%mod ) % mod;
				f[j][k+1] = (f[j][k+1] + ((ll)(abs(i+1-pb[k+1])<=d[1]) * f1[j][k]) % mod ) % mod;
				f[j+1][k] = (f[j+1][k] +  ((ll)(abs(i+1-pa[j+1])<=d[0]) * f1[j][k]) % mod ) % mod ;
			}
		}
		memcpy(f1, f, sizeof f);
	}
	printf("%d\n", f[a][b]);
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
