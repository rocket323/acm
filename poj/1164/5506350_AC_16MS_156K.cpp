#include<iostream>

using namespace std;

#define maxv 55

int mat[maxv][maxv];
int vis[maxv][maxv];
int step[4][2]={0,-1,-1,0,0,1,1,0};
int h,w;

int inM(int x,int y){
	if(x<0 || x>=h  || y<0 || y>=w)
		return 0;
	return 1;
}

void dfs(int x,int y,int &tmp){
	int i,j;
	int xx,yy;
	for(i=0;i<4;++i){
		if(((1<<i)&mat[x][y])==0 ){
			xx=x+step[i][0];
			yy=y+step[i][1];
			if(inM(xx,yy ) && !vis[xx][yy]){
				vis[xx][yy]=1;
				++tmp;
				dfs(xx,yy,tmp);
			}
		}
	}
}
void solve(){
	int i,j,k;
	int room;
	int ma;
	int tmp;
	for(i=0;i<h;++i){
		for(j=0;j<w;++j)
			scanf("%d",mat[i]+j);
	}
	memset(vis,0,sizeof(vis));
	room=0;
	ma=0;
	for(i=0;i<h;++i){
		for(j=0;j<w;++j){
			if(!vis[i][j]){
				++room;
				vis[i][j]=1;
				tmp=1;
				dfs(i,j,tmp);
				if(tmp > ma)
					ma=tmp;
			}
		}
	}
	printf("%d\n%d\n",room,ma);
}
int main(){
	while(scanf("%d%d",&h,&w)!=EOF){
		solve();
	}
	return 0;
}
