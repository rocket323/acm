#include <iostream>
using namespace std;

#define MAX 1000000010

int a[10001],l1,l2,l3,c1,c2,c3,n,i,j,k,s,t,f[10001]={0};

int getprice(int i,int j){
	int t;
	if(i>j){ t=i; i=j; j=t; }
	t=a[j]-a[i];
	if(t>0&&t<=l1) return c1;
	if(t<=l2) return c2;
	if(t<=l3) return c3;
	return MAX;
}

void process(){
	int i,j,k;
	f[s]=0; 
	for(i=s+1;i<=n;i++){
		f[i]=getprice(i,s);
		for(j=s;j<i;j++)
			if(f[j]+getprice(i,j)<f[i])
				f[i]=f[j]+getprice(i,j);
	}
	for(i=s-1;i>=1;i--){
		f[i]=getprice(i,s);
		for(j=s;j>i;j--)
			if(f[j]+getprice(i,j)<f[i])
				f[i]=f[j]+getprice(i,j);
	}
	cout<<f[t]<<endl;
}

int main(){
	scanf("%d%d%d%d%d%d",&l1,&l2,&l3,&c1,&c2,&c3);
	scanf("%d",&n);
	scanf("%d%d",&s,&t);
	a[0]=0;
	for(i=2;i<=n;i++) scanf("%d",&a[i]);
	process();
	return 0;
}
