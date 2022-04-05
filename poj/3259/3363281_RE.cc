#include <iostream>
#define MaxL 10000000
using namespace std;

long n,m,w,t,eda[20001],edb[2001],wei[2001],edage=0,dist[2001];

void init(){
	long i,j,k,a,b;
	cin>>n>>m>>w;
	edage=0;
	for(i=1;i<=m;i++){
		cin>>a>>b>>k;
		edage++;
		eda[edage]=a; edb[edage]=b; wei[edage]=k;
		edage++;
		eda[edage]=b; edb[edage]=a; wei[edage]=k;
	}
	for(i=1;i<=w;i++){
		cin>>a>>b>>k;
		edage++;
		eda[edage]=a; edb[edage]=b; wei[edage]=-k;
	}

}

void relax(long a,long b,long c){
	if(dist[a]+c<dist[b])
		dist[b]=dist[a]+c;
}

void process(){
	long i,j,k;
	for(i=1;i<=n;i++) dist[i]=MaxL;
	dist[1]=0;
	for(j=1;j<n;j++)
		for(i=1;i<=edage;i++)
			relax(eda[i],edb[i],wei[i]);
	for(i=1;i<=edage;i++)
		if(dist[eda[i]]+wei[i]<dist[edb[i]]){
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
