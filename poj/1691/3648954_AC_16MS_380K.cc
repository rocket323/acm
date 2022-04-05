#include <iostream>
#define MaxL 100000000
using namespace std;

struct node{
	int x1,y1,x2,y2;
	int col;
}re[16];

int N;
int nex[16], G[16][16], d[16], ans, Min;
int co[16];

bool check(int i, int j){
/*	if(i==2&&j==4){
		cout<<re[i].y1<<' '<<re[i].x1<<' '<<re[i].y2<<' '<<re[i].x2<<' '<<d[i]<<endl;
		cout<<re[j].y1<<' '<<re[j].x1<<' '<<re[j].y2<<' '<<re[j].x2<<' '<<d[j]<<endl;
		cout<<endl;
	}*/
/*	if(re[i].y2<=re[j].y1){
		if(re[i].x1>=re[j].x1&&re[i].x1<=re[j].x2)
			if(re[i].x2>=re[j].x1&&re[i].x2<=re[j].x2)
				return true;
	}
	return false;*/
	if(re[i].y2<=re[j].y1&&(re[i].x1-re[j].x2)*(re[i].x2-re[j].x1)<0) return true;
	return false;
}

void init(){
	int i,j,k;
	scanf("%d",&N);
	for(i=1;i<=N;i++)
		scanf("%d%d%d%d%d",&re[i].y1,&re[i].x1,&re[i].y2,&re[i].x2,&re[i].col);
	memset(d, 0, sizeof d);
	memset(nex, 0, sizeof nex);
	for(i=1;i<=N;i++)
		for(j=1;j<=N;j++)
			if(i!=j&&check(i, j)){
				d[j]++;
				nex[i]++;
				G[i][nex[i]]=j;
			}
	ans=MaxL;
	memset(co, -1, sizeof co);
}

void dfs(int brd, int bsh, int col){
	if(bsh>=ans) return;
	if(brd==N+1){
		ans=bsh;
		return;
	}
	int i, j;
	for(i=1;i<=N;i++){
		if(co[i]!=-1||d[i]!=0) continue;
		for(j=1;j<=nex[i];j++) d[G[i][j]]--;
		co[i]=1;
		if(col==-1){
			dfs(brd+1, bsh+1, re[i].col);
		}
		else if(re[i].col==col){
			dfs(brd+1, bsh, re[i].col);
		}
		else if(re[i].col!=col){
			dfs(brd+1, bsh+1, re[i].col);
		}
		for(j=1;j<=nex[i];j++) d[G[i][j]]++;
		co[i]=-1;
	}
}		

int main(){
	int i,j,k,T;
//	freopen("1691.in","r",stdin);
	scanf("%d",&T);
	for(i=1;i<=T;i++){
		init();
		dfs(1, 0, -1);
		printf("%d\n",ans);
	}
//	while(k=1);
	return 0;
}
