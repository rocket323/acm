#include <iostream>
#include <cmath>
using namespace std;

int n,m,s,v,g[101][101];
double x1[101],yy1[101],x2[101],y2[101];
bool used[101];
int link[101];

double dist(int s, int t){
	double ans;
	ans=sqrt((x1[s]-x2[t])*(x1[s]-x2[t])+(yy1[s]-y2[t])*(yy1[s]-y2[t]));
	return ans;
}

void init(){
	int i,j,k;
	cin>>m>>s>>v;
	for(i=1;i<=n;i++)
		cin>>x1[i]>>yy1[i];
	for(i=1;i<=m;i++)
		cin>>x2[i]>>y2[i];
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			if(dist(i,j)>s*v) g[i][j]=0;
			else g[i][j]=1;
		}
}

bool can(int x){
	int i,j,k;
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

void process(){
	int i,j,k,ans=0;
	memset(link,0,sizeof link);
	for(i=1;i<=n;i++){
		memset(used,0,sizeof used);
		if(can(i))
			ans++;
	}
	cout<<n-ans<<endl;
}

int main(){
	int i,j,k;
	while(cin>>n){
		init();
		process();
	}
	return 0;
}
