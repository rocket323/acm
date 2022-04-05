#include <stdio.h>
#define Mod 100000007
#define ll long long

int X, Y, x, y;
int f[2009][2009];

void init()
{
	for(int i=0; i<=2000; ++i)f[i][0] = f[i][i] = 1;
	for(int i=1; i<=2000; ++i)
	{
		for(int j=1; j<i; ++j) f[i][j] = ((ll)f[i-1][j] + f[i-1][j-1]) % Mod;
	}
}

int C(int n, int m)
{
	if(n<0 || m<0) return 0;
	if(m > n) return 0;
	else return f[n][m];
}

int getAns(int tun)
{
	int t = tun % 4;
	int p = tun / 4;
	int ans = 1;
	
	if((t==1 || t==2) && y==0) return 0;
	
	if(t==2)
	{
		ans = ((ll)ans * C(x-1, p)) % Mod;
		ans = ((ll)ans * C(Y-y, p)) % Mod;
		ans = ((ll)ans * C(X-x, p)) % Mod;
		ans = ((ll)ans * C(y, p)) % Mod;
	}
	else if(t==3)
	{
		ans = ((ll)ans * C(x-1, p)) % Mod;
		ans = ((ll)ans * C(Y-y, p+1)) % Mod;
		ans = ((ll)ans * C(X-x, p)) % Mod;
		ans = ((ll)ans * C(y, p)) % Mod;
	}
	else if(t==0)
	{
		ans = ((ll)ans * C(x-1, p-1)) % Mod;
		ans = ((ll)ans * C(Y-y, p)) % Mod;
		ans = ((ll)ans * C(X-x, p)) % Mod;
		ans = ((ll)ans * C(y, p-1)) % Mod;
	}
	else if(t==1)
	{
		ans = ((ll)ans * C(x-1, p-1)) % Mod;
		ans = ((ll)ans * C(Y-y, p)) % Mod;
		ans = ((ll)ans * C(X-x, p)) % Mod;
		ans = ((ll)ans * C(y, p)) % Mod;
	}
	return ans;
}

int solve()
{
	int ans = 0;
	
	if(x==0) return 1;
	
	if(y==0) ans++;
	
	for(int i=0; i<=X+Y+1; ++i)
	{
		ans = ( (ll)ans + getAns(i) ) % Mod;
	}
	
	return ans;
}

int main()
{
	int t;
	init();	
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &X, &Y, &x, &y);
		printf("%d\n", solve());
	}
	return 0;
}
