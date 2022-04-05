#include <iostream>
#define MaxL 100000000
using namespace std;

int n,m,dist[101],g[101][101];
bool used[101];

void init(){
	int i,j,k,a,b;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			g[i][j]=MaxL;
	for(i=1;i<=n;i++){
		cin>>m;
		for(j=1;j<=m;j++){
			cin>>a>>b;
			g[i][a]=b;
		}
	}
}

int dij(int s){
	int i,j,k,x,min,maxi;
	memset(used,0,sizeof used);
	for(i=1;i<=n;i++) dist[i]=MaxL;
	dist[s]=0;
	for(x=1;x<=n;x++){
		min=MaxL;
		for(i=1;i<=n;i++)
			if(dist[i]<min&&!used[i]){
				k=i;
				min=dist[i];
			}
		used[k]=true;
		for(i=1;i<=n;i++)
			if(dist[k]+g[k][i]<dist[i])
				dist[i]=dist[k]+g[k][i];
	}
	maxi=0;
	for(i=1;i<=n;i++)
		if(maxi<dist[i])
			maxi=dist[i];
	return maxi;
}	

void process(){
	int i,j,k,min=MaxL,rec=0;
	for(i=1;i<=n;i++){
		k=dij(i);
		if(k<min){
			min=k;
			rec=i;
		}
	}
	if(min==MaxL) cout<<"disjoint"<<endl;
	else cout<<rec<<' '<<min<<endl;
}

int main(){
	int i,j,k;
	cin>>n;
	while(n!=0){
		init();
		process();
		cin>>n;
	}
	return 0;
}
