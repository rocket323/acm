#include <iostream>
using namespace std;

struct node{
	int x, y;
	int lev;
}Q[90001];

bool vis[301][301];
int N,sx,sy,ex,ey, head, tail;
int dx[8]={2,1,-1,-2,-2,-1,1,2},
	dy[8]={1,2,2,1,-1,-2,-2,-1};

void init(){
	int i,j,k;
	scanf("%d",&N);
	scanf("%d%d",&sx,&sy);
	scanf("%d%d",&ex,&ey);
	memset(vis,0,sizeof vis);
	head=tail=1;
	Q[1].x=sx; Q[1].y=sy;
	Q[1].lev=0; 
	vis[sx][sy]=true;
}

void nextMove(){
	int i,j,k;
	for(k=0;k<8;k++){
		i=Q[head].x+dx[k]; j=Q[head].y+dy[k];
		if(i>=0&&i<N&&j>=0&&j<N&&!vis[i][j]){
			tail++;
			Q[tail].x=i; Q[tail].y=j;
			Q[tail].lev=Q[head].lev+1;
			vis[i][j]=true;
		}
	}
}

void process(){
	int i,j,k;
	while(head<=tail){
		if(Q[head].x==ex&&Q[head].y==ey){
			printf("%d\n",Q[head].lev);
			break;
		}
		nextMove();
		head++;
	}
}

int main(){
	int i,j,k,T;
//	freopen("1915.in","r",stdin);
	scanf("%d",&T);
	for(i=1;i<=T;i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
