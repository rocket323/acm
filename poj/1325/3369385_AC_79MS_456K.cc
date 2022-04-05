#include <iostream>
using namespace std;

int link[101],task,g[101][101],n,m;
bool used[101];

void init(){
	int i,j,k,a,b;
	memset(g,0,sizeof g);
	for(i=1;i<=task;i++){
		cin>>k>>a>>b;
		g[a][b]=1;
	}
}

bool can(int v){
	int i,j,k;
	for(i=1;i<=m;i++)
		if(!used[i]&&g[v][i]){
			used[i]=true;
			if(link[i]==0||can(link[i])){
				link[i]=v;
				return true;
			}
		}
	return false;
}

void process(){
	int i,j,k,ans=0;
	memset(link,0,sizeof link);
	for(i=1;i<=n;i++){
		memset(used,0,sizeof used);
		if(can(i)) ans++;
	}
	cout<<ans<<endl;
}

int main(){
	int i,j,k;
	cin>>n;
	while(n!=0){
		cin>>m>>task;
		init();
		process();
		cin>>n;
	}
	return 0;
}
