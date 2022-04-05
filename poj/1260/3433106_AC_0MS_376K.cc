#include <iostream>
#define Max 100000000
using namespace std;

int w[101],ned[101],f[101],n,sum[101];

void init(){
	int i,j,k;
	scanf("%d",&n);
	sum[0]=0;
	for(i=1;i<=n;i++){
		scanf("%d%d",&ned[i],&w[i]);
		sum[i]=sum[i-1]+ned[i];
	}
}

void process(){
	int i,j,k;
	f[0]=0;
	for(i=1;i<=n;i++){
		f[i]=Max;
		for(j=0;j<i;j++){
			k=w[i]*(sum[i]-sum[j]+10);
			if(f[j]+k<f[i])
				f[i]=f[j]+k;
		}
	}
	printf("%d\n",f[n]);
}

int main(){
	int i,j,k;
	scanf("%d",&k);
	for(i=1;i<=k;i++){
		init();
		process();
	}
	return 0;
}
