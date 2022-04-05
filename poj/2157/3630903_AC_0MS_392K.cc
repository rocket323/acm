#include <iostream>
using namespace std;

struct node{
	int x, y;
}Q[500];

int N,M;
int keys[80], sx, sy, head, tail;
bool open[80], vis[21][21];
int coll[80];
char G[21][21];
int dx[4]={0,-1,0,1}, dy[4]={1,0,-1,0};

void init(){
	int i,j,k;
	char cell;
	memset(keys, 0, sizeof keys);
	memset(open, 0, sizeof open);
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++){
			cin>>cell; G[i][j]=cell;
			if('a'<=cell&&cell<='e'){
				keys[(int)cell-32]++;
				continue;
			}
			if(cell=='S'){
				sx=i; sy=j;
				continue;
			}
		}
}

void pop(int i, int j){
	tail++;
	Q[tail].x=i; Q[tail].y=j;
	vis[i][j]=true;
}

void findKeys( ){
	int i, j, k, ii, jj, x, y;
	char cell;
	head=1; tail=1;
	memset(vis, 0, sizeof vis);
	memset(coll, 0, sizeof coll);
	Q[1].x=sx; Q[1].y=sy; vis[sx][sy]=1;
	while(head<=tail){
		x=Q[head].x; y=Q[head].y;
		for(i=0;i<4;i++){
			ii=x+dx[i]; jj=y+dy[i];
			if(ii>=1&&ii<=N&&jj>=1&&jj<=M&&!vis[ii][jj]&&G[ii][jj]!='X'){
				cell=G[ii][jj];
				if('a'<=cell&&cell<='e'){
					coll[(int)cell-32]++;
					pop(ii, jj);
					continue;
				}
				if('A'<=cell&&cell<='E'&&coll[(int)cell]==keys[(int)cell]){
					pop(ii, jj);
					continue;
				}
				else if(G[ii][jj]=='.'||G[ii][jj]=='G'){
					pop(ii, jj);
					continue;
				}
			}
		}
		head++;
	}
}

void work( ){
	int i,j,k, x, y, ii, jj;
	char cell;
	
	memset(vis, 0, sizeof vis);
	head=1; tail=1;
	Q[1].x=sx; Q[1].y=sy;
	vis[sx][sy]=1;
	while(head<=tail){
		if(G[Q[head].x][Q[head].y]=='G'){
			printf("YES\n");
			return;
		}
		x=Q[head].x; y=Q[head].y;
		for(i=0;i<4;i++){
			ii=x+dx[i]; jj=y+dy[i];
			if(ii>=1&&ii<=N&&jj>=1&&jj<=M&&G[ii][jj]!='X'&&!vis[ii][jj]){
				cell=G[ii][jj];
				if('A'<=cell&&cell<='E'&&coll[(int)cell]==keys[(int)cell]){
					pop(ii, jj);
					continue;
				}
				else if(!('A'<=cell&&cell<='E')){
					pop(ii, jj);
					continue;
				}
			}
		}
		head++;
	}
	printf("NO\n");
}

void process(){
	int i,j,k;
	findKeys( );
	work( );
}

int main(){
	int i,j,k;
	scanf("%d%d",&N,&M);
	while(N!=0){
		init();
		process();
		scanf("%d%d",&N,&M);
	}
	return 0;
}
