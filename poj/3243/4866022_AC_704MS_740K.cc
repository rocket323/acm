#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

#define N 31630
#define llong __int64

int T[N];
int I[N];
int x,z,k,l;

llong mod(llong a,llong b,llong n)
{
	llong ret;
	
	for(ret=1;b;b>>=1,a=a*a%n)
		if(b&1)
			ret=ret*a%n;
	return ret;
}
llong ext_gcd(llong a,llong b,llong& x,llong& y)
{
	llong t,ret;
	if (!b){
		x=1,y=0;
		return a;
	}
	ret=ext_gcd(b,a%b,x,y);
	t=x,x=y,y=t-a/b*y;
	return ret;
}
llong emod(llong a,llong b,llong n,llong* sol){
	llong d,e,x,y,i;
	d=ext_gcd(a,n,x,y);
	if (b%d)
		return 0;
	e=(x*(b/d)%n+n)%n;
	for (i=0;i<d;i++)
		sol[i]=(e+i*(n/d))%n;
	return d;
}
int sol()
{
	llong i,al,v,all;
	llong sol[1000];
	all=mod(x,l,z);
	al=1;
	for(i=0;i<l;i++)
	{
		llong d=emod(al,k,z,sol);
		for(int j=0;j<d;j++)
		{
			llong tt=sol[j];
			if(tt!=-1)
			{
				v=lower_bound(T,T+l,tt)-T;
				if(v<l&&T[v]==tt)
					return i*l+I[v];
			}
		}
		al=al*all%z;
	}
	return -1;
}
int cmp(int a,int b)
{
	return T[a]<T[b];
}
int main()
{
	int i;
	//freopen("dd.in","r",stdin);
	while(scanf("%d%d%d",&x,&z,&k)&&z)
	{
		k%=z;
		x%=z;
		//printf("%d\n",mod(801803,857648,14763441));
		l=(int)sqrt(z)+1;
		I[0]=0;
		T[0]=1;
		for(i=1;i<l;i++)
		{
			T[i]=(llong)T[i-1]*x%z;
			I[i]=i;
		}
		stable_sort(I,I+l,cmp);
		sort(T,T+l);
		int ans=sol();
		/*int tt;
		scanf("%d",&tt);
		if(ans!=tt)
		{
			printf("%d %d %d\n",x,z,k);
			printf("%d %d\n",ans,tt);
		}*/
		if(ans==-1)
			printf("No Solution\n");
		else
			printf("%d\n",ans);
	}
	return 0;
}

