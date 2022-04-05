#include <iostream>
#define Max 100000000
using namespace std;

int ans=Max,n,m,g[11][100],num[11]={0};
int p[11][100],r[11][100],c[11][100];
int vis[11]={0};

void init(){
	int i,j,k;
	int a,b,x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++){ 
		scanf("%d%d%d%d%d",&a,&b,&x,&y,&z);
		num[a]++;
		g[a][num[a]]=b;
		c[a][num[a]]=x;
		p[a][num[a]]=y;
		r[a][num[a]]=z;
	}
	vis[1]=1;
}

void search(int id, int cost){
	if(cost>ans) return;
	if(id==n){
		ans=cost;
		return;
	}
	int i,j,k,tmp;
	for(i=1;i<=num[id];i++){
		k=g[id][i];
		if(vis[k]<2){
			if(vis[c[id][i]]){
				vis[k]++;
				search(k,cost+p[id][i]);
				vis[k]--;
			}
			else{
				vis[k]++;
				search(k,cost+r[id][i]);
				vis[k]--;
			}
		}
	}
}

int main(){
	int i,j,k;
	init();
	search(1,0);
	if(ans<Max)
		printf("%d\n",ans);
	else printf("impossible\n");
	return 0;
}
