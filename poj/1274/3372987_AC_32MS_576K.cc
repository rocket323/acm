#include <iostream>
using namespace std;

int link[201]={0},g[201][201]={0},n,m;
bool used[201];

void init(){
	int i,j,b,k;
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
	int i,j,k;
	for(i=1;i<=m;i++)
		if(!used[i]&&g[x][i]){
			used[i]=1;
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
	cout<<ans<<endl;
}		

int main(){
	int i,j,k;
	while(cin>>n){
		init();
		maxMatch();
	}
	return 0;
}
