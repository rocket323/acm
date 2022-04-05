#include <stdio.h>
#include <cstring>
#define ll long long
#define Mod 9901

int A[100], B[100], top;

void init(int n)
{
	top = 0;
	memset(B, 0, sizeof B);
	for(int i=2; i*i<=n; ++i)
	{
		if(n%i==0){ top++; A[top] = i; }
		while(n%i==0)
		{
			B[top]++;
			n /= i;
		}
	}
	if(n > 1){ A[++top] = n; B[top] = 1; }
}

int mod(int x, int m)
{
	return (x%m + m) % m;
}

void gcd(int a, int b, int& d, int& x, int& y)
{
	if(b==0){ d=a; x=1; y=0; }
	else
	{
		gcd(b, a%b, d, y, x);
		y -= x*(a/b);
	}
}

int pow(int a, int n)
{
	if(n==0) return 1;
	int tmp = pow(a, n/2);
	tmp = ((ll)tmp * tmp)%Mod;
	if(n&1) tmp = ((ll)tmp * a) % Mod;
	return tmp;
}

int go(int p, int a, int b)
{

	if(A[p]%Mod==1)
	{
		return (B[p]*b+1)%Mod;
	}

	int u = pow(A[p] % Mod, B[p]*b + 1);
	int v=  (A[p] - 1);
	u = (u + Mod -1) % Mod;
	
	int d, x, y;
	gcd(v, Mod, d, x, y);
	x *= u;
	return mod(x, Mod);
}

int solve(int a, int b)
{
	if(a==0) return 0;
	init(a);
	int ans = 1;
	for(int i=1; i<=top; ++i)
	{
		int k = go(i, a, b);
		ans = ((ll)ans * k) % Mod;
	}
	return ans;
}

int main()
{
	int a, b;
	while(scanf("%d%d", &a, &b)!=EOF)
	{
		printf("%d\n", solve(a, b));
	}
	return 0;
}
