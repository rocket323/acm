#include <iostream>
using namespace std;

struct node{
	int x,y;
	int len;
} ;
node A[1251],B[1251];
int n,m,tn,ttmm,link[1251]={0};
bool w[1251][1251]={0},g[51][51],used[1251];

bool cross(int a1,int a2){
	int i,j,k;
	bool f1,f2;
	f1=(A[a1].y<=B[a2].y&&B[a2].y<=A[a1].y+A[a1].len-1);
	f2=(B[a2].x<=A[a1].x&&A[a1].x<=B[a2].x+B[a2].len-1);
	if(f1&&f2) return true;
	return false;
}

bool can(int x){
	int i,j,k;
	for(i=1;i<=ttmm;i++)
		if(!used[i]&&w[x][i]){
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
	for(i=1;i<=tn;i++){
		memset(used,0,sizeof used);
		if(can(i)) ans++;
	}
	cout<<ans<<endl;
}

void init(){
	int i,j,k,len;
	char ch;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			cin>>ch;
			if(ch=='*') g[i][j]=1;
			else g[i][j]=0;
		}
	}
	for(i=1;i<=n;i++){
		j=1;
		while(j<m){
			while(g[i][j]==0) j++;
			if(j>m) break;
			tn++; len=0;
			A[tn].x=i; A[tn].y=j;
			while(g[i][j]==1&&j<=m) j++;
			j--;
			A[tn].len=j-A[tn].y+1;
			j++;
		}
	}
	for(i=1;i<=m;i++){
		j=1;
		while(j<n){
			while(g[j][i]==0) j++;
			if(j>n) break;
			ttmm++; len=0;
			B[ttmm].x=j; B[ttmm].y=i;
			while(g[j][i]==1&&j<=n) j++;
			j--;
			B[ttmm].len=j-B[ttmm].x+1;
			j++;
		}
	}
	for(i=1;i<=tn;i++)
		for(j=1;j<=ttmm;j++){
			if(cross(i,j)) w[i][j]=1;
		}
	
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}
