#include <iostream>
#define MaxL 520
#define ll long long
#define mod 20090305 
using namespace std;

int d[3];
char S[MaxL];
int f[MaxL][MaxL][MaxL];
int pa[MaxL], pb[MaxL], pc[MaxL], a, b, c;

void init()
{
	memset(d, 0, sizeof d);
	for(int i=0; i<3; ++i) scanf("%d", &d[i]);
	cin >> S;
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
	f[0][0][0] = 1;
	int len = strlen(S);
	for(int i=0; i<=len; ++i)
	{
		for(int j=0; j<=i; ++j)
		{
			for(int k=0; k<=i-j; ++k)
			{	
				f[i+1][j][k] = (f[i+1][j][k] + ((ll)(abs(i+1-pc[i+1-j-k])<=d[2]) * f[i][j][k])%mod ) % mod;
				f[i+1][j][k+1] = (f[i+1][j][k+1] + ((ll)(abs(i+1-pb[k+1])<=d[1]) * f[i][j][k]) % mod ) % mod;
				f[i+1][j+1][k] = (f[i+1][j+1][k] +  ((ll)(abs(i+1-pa[j+1])<=d[0]) * f[i][j][k]) % mod ) % mod ;
			}
		}
	}
	printf("%d\n", f[len][a][b]);
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
