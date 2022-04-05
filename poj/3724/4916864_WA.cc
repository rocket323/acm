#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;

int n;
double x[21], y[21], E[20];
int a[11], flag;

void init()
{
	for(int i=0; i<n; ++i) scanf("%lf%lf", &x[i], &y[i]);
	E[0] = 1.0;
	for(int i=1; i<20; ++i) E[i] = E[i-1] * 0.1;
}

double mypow(double x, int n)
{
	if(n==0) return 1.0;
	double mid = mypow(x, n/2);
	if(n&1) return mid * mid * x;
	else return mid * mid;
}

int cmp(double y1, double y2)
{
	double eps = 9.999999;
	double yy = fabs(y2);
	int k = yy;
	yy = yy - k;
	stringstream in;
	char s[20];
	in << yy;
	in >> s;
	int len = strlen(s);
	//cout<<yy<<' '<<len<<endl;
	eps = E[len-2];
	
	if(fabs(y1-y2) > eps) return 0;
	else return 1;
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
		if(!cmp(tmp, y[i])) return 0;
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
	//cout<<1<<endl;
	dfs(0, 1);
	//cout<<2<<endl;
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
