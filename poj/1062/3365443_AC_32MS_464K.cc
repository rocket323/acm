#include <iostream>
#include <cmath>
#define MaxL 100000000
using namespace std;

int g[101][101]={0},num[101]={0},n,m,w[101]={0},lev[101],dist[101]={0};
int s[101],t[101],a[101],tp=0;
bool used[101]={0};

void init(){
	int i,j,k,u,v,center;
	cin>>m>>n;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			g[i][j]=MaxL;
	for(i=1;i<=n;i++){
		cin>>w[i]>>lev[i]>>k;
		for(j=1;j<=k;j++){
			cin>>u>>v;
			g[i][u]=v;
		}
		a[i]=lev[i];
	}
	
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
			if(a[i]>a[j]){
				k=a[i]; a[i]=a[j]; a[j]=k;
			}
	for(center=1;center<=n;center++)
		if(a[center]==lev[1])
			break;
	
	for(i=1;i<=center;i++)
		if(lev[1]-a[i]<=m){
			tp++;
			for(j=center;j<n;j++)
				if(a[j]-a[i]>m)
					break;
			if(a[j]-a[i]>m) j--;
			s[tp]=a[i]; t[tp]=a[j];
		}
	//cout<<tp<<endl;
	//for(i=1;i<=tp;i++) cout<<s[i]<<' '<<t[i]<<endl;
}

int dij(int s,int t){
	int x,i,j,k,min;
	memset(used,0,sizeof used);
	for(i=1;i<=n;i++) dist[i]=MaxL;
	dist[1]=0;
	for(x=1;x<=n;x++){
		min=MaxL;
		for(i=1;i<=n;i++)
			if(min>dist[i]&&!used[i]&&lev[i]>=s&&lev[i]<=t){
				min=dist[i];
				k=i;
			}
		used[k]=true;
		for(j=1;j<=n;j++)
			if(g[k][j]<MaxL&&lev[j]>=s&&lev[j]<=t)
				if(dist[j]>dist[k]+g[k][j])
					dist[j]=dist[k]+g[k][j];
	}
	min=MaxL;
	for(i=1;i<=n;i++)
		if(lev[i]>=s&&lev[i]<=t)
			if(dist[i]+w[i]<min)
				min=dist[i]+w[i];
	return min;
}

void process(){
	int i,j,k,min=MaxL;
	for(i=1;i<=tp;i++){
		k=dij(s[i],t[i]);
		if(k<min)
			min=k;
	}
	cout<<min<<endl;
}

int main(){
	int i,j,k,a,b;
	init();
	process();
	return 0;
}
