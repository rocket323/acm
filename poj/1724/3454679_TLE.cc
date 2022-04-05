#include <iostream>
#define Max 100000000
using namespace std;

int n,path,mon;
int g[101][101],num[101]={0},p[101][101],m[101][101];
bool vis[101]={0};

void init(){
	int i,j,k,a,b,l,r,t;
	scanf("%d%d%d",&mon,&n,&r);
	for(i=1;i<=r;i++){
		scanf("%d%d%d%d",&a,&b,&l,&t);
		num[a]++;
		g[a][num[a]]=b;
		p[a][num[a]]=l;
		m[a][num[a]]=t;
	}
	vis[1]=1;
	path=Max;
}

void search(int id, int curp, int curm){
	if(curp>path) return;
	if(id==n){
		path=curp;
		return;
	}
	int i,k;
	for(i=1;i<=num[id];i++){
		k=g[id][i];
		if(!vis[k])
			if(curm+m[id][i]<=mon){
				vis[k]=1;
				search(k, curp+p[id][i], curm+m[id][i]);
				vis[k]=0;
			}
	}
}			

int main(){
	init();
	search(1,0,0);
	if(path<Max) printf("%d\n",path);
	else printf("-1\n");
	return 0;
}
