#include <iostream>
#define Mod 1000000000
using namespace std;

int n,f[10000000];
int a[21],tp;

void init(){
	int i,j,k;
	scanf("%d",&n);
	a[1]=1; tp=1;
	while(a[tp]*2<n){
		tp++;
		a[tp]=a[tp-1]*2;
	}
}

void process(){
	int i,j,k;
	memset(f,0,sizeof f);
	f[0]=1;
	for(i=1;i<=tp;i++)
		for(j=a[i];j<=n;j++)
			f[j]=(f[j]+f[j-a[i]])%Mod;
	printf("%d\n",f[n]);
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}
