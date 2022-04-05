#include <iostream>
using namespace std;

int N, H[3001], f[3001];

void process(int tes){
	int i,j,k, ans=0;
	for(i=1;i<=N;i++) f[i]=1;
	for(i=2;i<=N;i++){
		for(j=1;j<i;j++)
			if(H[j]>H[i]&&f[j]+1>f[i])
				f[i]=f[j]+1;
		if(f[i]>ans) ans=f[i];
	}
	printf("Test #%d:\n", tes);
	printf("  maximum possible interceptions: %d\n\n",ans);
}

int main(){
	int i,j,k,tes=0;
//	freopen("1887.in","r",stdin);
	N=0;
	while(cin>>k){
		if(k!=-1){
			N++;
			H[N]=k;
		}
		else{
			if(N!=0)
				process(++tes);
			N=0;
		}
	}
//	while(k=1);
	return 0;
}
