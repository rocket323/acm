#include <iostream>
#define MaxN 10001
using namespace std;

int d[MaxN], N, M;
int f1[501], f[501], g[501], g1[501];

int Max(int a, int b){
	return(a>b)?a:b;
}

int main(){
	int i,j,k;
//	freopen("cowrun.4.in","r",stdin);
	cin>>N>>M;
	for(i=1;i<=N;i++){
		cin>>d[i];
	}
	memset(f1, 0, sizeof f1);
	memset(g1, 0, sizeof g1);
	for(i=1;i<=N;i++){
		for(j=0;j<=M;j++){
			if(j==0){
				f[j]=Max(f1[j], Max(f1[j+1], g1[j+1]));
				g1[j]=0;
			}
			else if(j==M){
				f[j]=0;
				g[j]=Max(f1[0]+d[i], g1[j-1]+d[i]);
			}
			else{
				f[j]=Max(f1[j+1], g1[j+1]);
				g[j]=Max(f1[0]+d[i], g1[j-1]+d[i]);
			}
		}
		memcpy(f1, f, sizeof f);
		memcpy(g1, g, sizeof g);
	}
	cout<<f[0]<<endl;
//	while(k=1);
	return 0;
}