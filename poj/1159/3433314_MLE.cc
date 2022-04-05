#include <iostream>
#define Max 1000000000
using namespace std;

unsigned int f[5001][5001],n;
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
	memset(f,0,sizeof f);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(i<j) f[i][j]=Max;

	for(k=2;k<=n;k++)
		for(i=1;i<=n+1-k;i++){
			j=i+k-1;
			t=(a[i]==a[j])?0:1;
			f[i][j]=Min(f[i][j], f[i+1][j-1]+t, f[i][j-1]+1, f[i+1][j]+1);
		}
	printf("%d\n",f[1][n]);
	return 0;
}
