#include <iostream>
#include <cmath>
using namespace std;

long n,d,ans,test=0,x[1001],y[1001],maxy=-1;

void init(){
	long i,j,k;
	for(i=1;i<=n;i++){
		cin>>x[i]>>y[i];
		if(y[i]>maxy) maxy=y[i];
	}
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
			if(x[i]>x[j]){
				k=x[i]; x[i]=x[j]; x[j]=k;
				k=y[i]; y[i]=y[j]; y[j]=k;
			}
}

void bing(double& l,double& r,double x1,double x2){
	long i,j,k;
	if(x1>=l) l=x1;
	if(x2<=r) r=x2;
}

long findRight(long t){
	long ans,i,j,k;
	double r1,r2,r3,r4;
	r1=x[t]-sqrt(d*d-y[t]*y[t]); r2=x[t]+sqrt(d*d-y[t]*y[t]);
	for(i=t+1;i<=n;i++){
		r3=x[i]-sqrt(d*d-y[i]*y[i]); r4=x[i]+sqrt(d*d-y[i]*y[i]);
		if(r3<=r2)
			bing(r1,r2,r3,r4);
		else return i-1;
	}
	return n;
}
long process(){
	long left=1,ans=0,i,j,k;
	if(maxy>d) return -1;
	while(left<=n){
		k=findRight(left);
		ans++;
		left=k+1;
	}
	return ans;
}
int main(){
	int k;
	cin>>n>>d;
	while(!(n==0&&d==0)){
		init();
		ans=process();
		test++;
		printf("Case %d: %d\n",test,ans);
		cin>>n>>d;
	}
	return 0;
}
