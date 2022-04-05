#include <iostream>
using namespace std;

int g[301][301],link[301],n,m;
bool used[301];

void init(){
	int i,j,k,b;
	cin>>m;
	memset(g,0,sizeof g);
	for(i=1;i<=n;i++){
		cin>>k;
		for(j=1;j<=k;j++){
			cin>>b;
			g[i][b]=1;
		}
	}
}

bool can(int x){
	int i,j;
	for(i=1;i<=m;i++)
		if(!used[i]&&g[x][i]){
			used[i]=true;
			if(link[i]==0||can(link[i])){
				link[i]=x;
				return true;
			}
		}
	return false;
}

void maxMatch(){
	int i,j,k,ans=0;
	memset(link,0,sizeof link);
	for(i=1;i<=n;i++){
		memset(used,0,sizeof used);
		if(can(i)) ans++;
	}
	if(ans!=n) cout<<"NO"<<endl;
	else cout<<"YES"<<endl;
}

int main(){
	int i,j,k;
	while(cin>>n){
		init();
		if(n!=m){
			cout<<"NO"<<endl;
			continue;
		}
		maxMatch();
	}
	return 0;
}
