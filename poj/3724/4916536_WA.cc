#include <iostream>
#include <cmath>
#define eps 1e-3
using namespace std;

int n;
double x[21], y[21], E;
int a[11], flag;

void init()
{
	for(int i=0; i<n; ++i) scanf("%lf%lf", &x[i], &y[i]);
}

double mypow(double x, int n)
{
	if(n==0) return 1.0;
	double mid = mypow(x, n/2);
	if(n&1) return mid * mid * x;
	else return mid * mid;
}

int check()
{
	for(int i=0; i<n; ++i)
	{
		double t = exp(x[i]), tmp = 0;
		for(int j=0; j<10; ++j)
		{
			tmp += mypow(t, a[j]);
			//if(tmp > y[i]) return 0;
		}
		if(fabs(tmp - y[i]) > eps) return 0;
	}
	return 1;
}

void dfs(int pos, int la)
{
	if(pos==10)
	{
		if(check()) flag = 1;
		return;
	}
	for(int i=la; i<=10; ++i)
	{
		a[pos] = i;
		dfs(pos+1, i);
		if(flag) return;	
	}
}

void solve()
{
	memset(a, -1, sizeof a);
	flag = 0;
	dfs(0, 1);
	//for(int i=0; i<n; ++i) cout<<x[i]<<' '<<y[i]<<endl;
	for(int i=0; i<10; ++i) printf("%d\n", a[i]);
}

int main()
{
	while(scanf("%d", &n)!=EOF)
	{
		init();
		solve();
	}
	return 0;
}
