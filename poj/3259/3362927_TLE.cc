#include <iostream>
#define MaxL 10000000
using namespace std;

long g[501][501],dist[501],n,m,w,t;

void init(){
	long i,j,k,a,b;
	cin>>n>>m>>w;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++) 
			g[i][j]=MaxL;
	for(i=1;i<=m;i++){
		cin>>a>>b>>k;
		if(k<g[a][b]){
			g[a][b]=k; g[b][a]=k;
		}
	}
	for(i=1;i<=w;i++){
		cin>>a>>b>>k;
		g[a][b]=-k;
	}
	/*for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)
			cout<<i<<' '<<j<<' '<<g[i][j]<<' '<<endl;
		cout<<endl;
	}*/
}

bool makeIt(long x){
	long i,j,k; bool quit=false;
	for(i=1;i<=n;i++) dist[i]=MaxL;
	dist[x]=0;
	while(!quit){
		quit=true;
		for(i=1;i<=n;i++)
			if(dist[i]<MaxL)
				for(j=1;j<=n;j++)
					if(dist[i]+g[i][j]<dist[j]){
						dist[j]=dist[i]+g[i][j];
						quit=false;
					}
		if(dist[x]<0) break;
	}
	//cout<<x<<' '<<dist[x]<<endl;
	return dist[x]<0;
}		

void process(){
	long i,j,k;
	for(i=1;i<=n;i++)
		if(makeIt(i)){
			cout<<"YES"<<endl;
			return;
		}
	cout<<"NO"<<endl;
}

int main(){
	long i,j,k;
	cin>>t;
	for(i=1;i<=t;i++){
		init();
		process();
	}
	return 0;
}
