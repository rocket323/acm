#include <iostream>
#include <cmath>
#define MaxL 100000000
using namespace std;

int g[101][101]={0},num[101]={0},n,m,w[101]={0},lev[101],dist[101]={0};
bool used[101]={0};

void init(){
	int i,j,k,a,b;
	cin>>m>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			g[i][j]=MaxL;
	for(i=1;i<=n;i++){
		cin>>w[i]>>lev[i]>>k;
		for(j=1;j<=k;j++){
			cin>>a>>b;
			g[i][a]=b;
		}
	}
}

void dij(){
	int x,i,j,k,min;
	for(i=1;i<=n;i++) dist[i]=MaxL;
	dist[1]=0;
	for(x=1;x<=n;x++){
		min=MaxL;
		for(i=1;i<=n;i++)
			if(min>dist[i]&&!used[i]){
				min=dist[i];
				k=i;
			}
		used[k]=true;
		for(j=1;j<=n;j++)
			if(g[k][j]<MaxL&&abs(lev[k]-lev[j])<=m)
				if(dist[j]>dist[k]+g[k][j])
					dist[j]=dist[k]+g[k][j];
	}
}

void process(){
	int i,j,k,min=MaxL;
	dij();
	for(i=1;i<=n;i++)
		if(dist[i]+w[i]<min)
			min=dist[i]+w[i];
	cout<<min<<endl;
}
			
int main(){
	int i,j,k,a,b;
	init();
	process();
	return 0;
}
