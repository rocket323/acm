#include <iostream>
#include <cmath>
using namespace std;

int n,m,hole;
int lx[600],rx[600],g[600][600],used[600],link[600],col[33][33],a[600][600],rt=0,lt=0;
int ly[600],ry[600];

void getcol(){
	int i,j,k;
	for(i=1;i<=32;i++)
		for(j=1;j<=32;j++)
			if((i+j)%2==0)
				col[i][j]=0;
			else col[i][j]=1;
}

bool adj(int x1,int x2,int y1, int y2){
	if(x1==x2&&abs(y1-y2)==1) return true;
	if(y1==y2&&abs(x1-x2)==1) return true;
	return false;
}

void init(){
	int i,j,k,x1,x2;
	cin>>n>>m>>hole;
	memset(a,0,sizeof a);
	for(i=1;i<=hole;i++){
		cin>>x1>>x2;
		a[x2][x1]=1;
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(a[i][j]==0)
				if(col[i][j]==1){
					lt++;
					lx[lt]=i; ly[lt]=j;
				}
				else if(col[i][j]==0){
					rt++;
					rx[rt]=i; ry[rt]=j;
				}
	for(i=1;i<=lt;i++)
		for(j=1;j<=rt;j++)
			if(adj(lx[i],rx[j],ly[i],ry[j]))
				g[i][j]=1;
			else g[i][j]=0;
}

bool can(int x){
	int i,j,k;
	for(i=1;i<=rt;i++)
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
	int i,j,k,ans;
	memset(link,0,sizeof link);
	ans=0;
	if(rt!=lt) { cout<<"NO"<<endl; return;}
	for(i=1;i<=lt;i++){
		memset(used,0,sizeof used);
		if(can(i)) ans++;
	}
	if(ans==rt) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
}

int main(){
	int i,j,k;
	getcol();
	init();
	maxMatch();
	return 0;
}
