#include <iostream>
#include <cmath>
#define MM 10000000
using namespace std;

int n,f,Max,a[100001], s[1000001];
double opt[1000001],gg[1000001];
const double eps=1e-9;

void init(){
	int i,j,k;
	scanf("%d%d",&n,&f);
	Max=-MM; s[0]=0;
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]>Max) Max=a[i];
		s[i]=s[i-1]+a[i];
	}
}

double MaxN(double a, double b){
	return (a>b)?a:b;
}

double DP(double ave){
	int i,j,k,cnt=0;
	double MaxS=-MM;
	gg[1]=a[1]-ave;
	for(i=2;i<=n;i++)
		gg[i]=MaxN(gg[i-1]+a[i]-ave, a[i]-ave);
	
	opt[f]=s[f]-ave*f;
		
	if(opt[f]>MaxS) MaxS=opt[f];
	for(i=f+1;i<=n;i++){
		opt[i]=MaxN(gg[i-f]+(s[i]-s[i-f]-ave*f), s[i]-s[i-f]-ave*f);
		if(opt[i]>MaxS)
			MaxS=opt[i];
	}
	return MaxS;
}

void process(){
	int i,j,k,TT;
	double mid, ans=-MM;
	double l=0, r=Max;
	while(l<=r+eps){
		mid=(l+r)/2.00;
		if(DP(mid)>=0.0){
			ans=MaxN(ans,mid);
			l=mid+eps;
		}
		else{
			r=mid-eps;
		}
	}
	printf("%.0f\n",1000*ans);
}

int main(){
	int i,j,k;
//	freopen("2018t.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
