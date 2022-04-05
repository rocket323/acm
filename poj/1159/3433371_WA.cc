#include <iostream>
#define Max 1000000000
using namespace std;

int f[5001],f1[5001],f2[5001],n;
char a[5001];

int Min(int a, int b, int c, int d){
	int t=Max;
	if(t>a) t=a;
	if(t>b) t=b;
	if(t>c) t=c;
	if(t>d) t=d;
}

int main(){
	int i,j,k,t;
	scanf("%d",&n);
	scanf("%s",a);
	memset(f1,0,sizeof f1);
	memset(f2,0,sizeof f2);
	for(k=2;k<=n;k++){
		for(i=1;i<=n+1-k;i++){
			f[i]=Max;
			j=i+k-1;
			t=(a[i-1]==a[j-1])?0:2;
			f[i]=Min(f[i], f2[i+1]+t, f1[i]+1, f1[i+1]+1);
		}
		memcpy(f2,f1,sizeof f1);
		memcpy(f1,f,sizeof f);
	}
	printf("%d\n",f[1]);
	return 0;
}
