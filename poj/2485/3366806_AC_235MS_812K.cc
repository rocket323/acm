#include <iostream>
#define MaxL 100000000
using namespace std;

int n,g[501][501],closet[501],lowcost[501];
bool s[501];

void init(){
	int i,j,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			scanf("%d",&g[i][j]);
		}
	}
}

void prim(){
	int i,j,k,min,rec,tot,maxn;
	tot=0; maxn=0;
	memset(s,0,sizeof s);
	s[1]=true;
	for(i=2;i<=n;i++){
		lowcost[i]=g[i][1];
		closet[i]=1;
	}
	for(i=1;i<n;i++){
		min=MaxL;
		for(j=2;j<=n;j++)
			if(lowcost[j]<min&&!s[j]){
				rec=j;
				min=lowcost[j];
			}
		s[rec]=true;
		if(maxn<min) maxn=min;
		for(k=2;k<=n;k++)
			if(!s[k]&&lowcost[k]>=g[k][rec]){
				lowcost[k]=g[k][rec];
				closet[k]=rec;
			}
	}
	cout<<maxn<<endl;
}

int main(){
	int t,i,j,k;
	scanf("%d",&t);
	for(i=1;i<=t;i++){
		init();
		prim();
	}
	return 0;
}
