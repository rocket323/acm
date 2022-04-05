#include <iostream>
#define MM 10000000
using namespace std;

int n,f,Max,a[100001];
const double eps=1e-9;

void init(){
	int i,j,k;
	scanf("%d%d",&n,&f);
	Max=-MM;
	for(i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]>Max) Max=a[i];
	}
}

double MaxN(double a, double b){
	return (a>b)?a:b;
}

double DP(double ave){
	int i,j,k,cnt=0;
	double sum=0, MaxS=-MM;
	for(i=1;i<=n;i++){
		sum+=(a[i]-ave); cnt++;
		if(sum<0){
			cnt=0;
			sum=0;
			continue;
		}
		if(sum>MaxS&&cnt>=f)
			MaxS=sum;
	}
	return MaxS;
}

void process(){
	int i,j,k,TT;
	double mid, ans=-MM;
	double l=0, r=Max;
	while(l<=r+eps){
		mid=(l+r)/2.00;
		//cout<<mid<<endl;
		if(DP(mid)>=0){
			ans=MaxN(ans,mid);
			l=mid+eps;
		}
		else
			r=mid-eps;
	}
	printf("%.0f\n",1000*ans);
}

int main(){
	int i,j,k;
//	freopen("2018.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
