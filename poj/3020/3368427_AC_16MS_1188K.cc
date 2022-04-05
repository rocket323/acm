#include <iostream>
#include <cmath>
using namespace std;
//覆盖问题，ans=点数-最大匹配数 
int n,m,color,num,col[41][11],link[501],g[501][501];
int ord[501],x[501],y[501];
bool used[501];

bool adj(int a, int b){
	int x1,x2,y1,y2;
	x1=x[a]; x2=x[b];
	y1=y[a]; y2=y[b];
	if(x1==x2&&abs(y1-y2)==1) return true;
	if(y1==y2&&abs(x1-x2)==1) return true;
	return false;
}

void init(){
	int i,j,k;
	char ch;
	cin>>n>>m;
	num=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++){
			cin>>ch;
			if(ch=='*'){
				num++;
				x[num]=i; y[num]=j;
				ord[num]=col[i][j];
			}
		}
	for(i=1;i<=num;i++)
		for(j=1;j<=num;j++)
			if(i!=j&&ord[i]==1)
				if(adj(i,j)) g[i][j]=1;
				else g[i][j]=0;
}

bool can(int x){
	int i,j,k;
	for(i=1;i<=num;i++)
		if(ord[i]==0)
			if(!used[i]&&g[x][i]){
				used[i]=1;
				if(link[i]==0||can(link[i])){
					link[i]=x;
					return true;
				}
			}
	return false;
}

void process(){
	int i,j,k,ans;
	ans=0;
	memset(link,0,sizeof link);
	for(i=1;i<=num;i++)
		if(ord[i]==1){
			memset(used,0,sizeof used);
			if(can(i)) ans++;
		}
	cout<<num-ans<<endl;
}

void getcol(){
	int i,j,k;
	for(i=1;i<=40;i++)
		for(j=1;j<=10;j++)
			if((i+j)%2==0)
				col[i][j]=0;
			else col[i][j]=1;
}

int main(){
	int i,j,k;
	cin>>k;
	getcol();
	for(i=1;i<=k;i++){
		init();
		process();
	}
	return 0;
}
	
