#include <iostream>
#define MaxL 100001
using namespace std;

int n,m,opp[MaxL], pre[MaxL];

void init(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=0;i<=n;i++) pre[i]=i;
	memset(opp,0,sizeof opp);
}

int find(int x){
	int k;
	if(pre[x]==x) return x;
	k=find(pre[x]);
	pre[x]=k;
	return k;
}

void process(){
	int i,j,k,a,b,x,y,u,v;
	char s[6];
	for(i=1;i<=m;i++){
		scanf("%s%d%d",s,&a,&b);
		if(s[0]=='A'){
			x=find(a); y=find(b);
			if(x==y){
				printf("In the same gang.\n");
				continue;
			}
			x=find(opp[a]);
			if(x==y){
				printf("In different gangs.\n");
				continue;
			}
			printf("Not sure yet.\n");
		}
		else{
			x=find(a); y=find(b);
			if(opp[x]==0&&opp[y]==0){
				opp[x]=y; opp[y]=x;
				continue;
			}
			if(opp[x]!=0&&opp[y]==0){
				u=find(opp[x]);
				pre[y]=u; opp[u]=x;
				continue;
			}
			if(opp[x]==0&&opp[y]!=0){
				v=find(opp[y]);
				pre[x]=v; opp[v]=y;
				continue;
			}
			if(opp[x]!=0&&opp[y]!=0){
				u=find(opp[x]); v=find(opp[y]);
				pre[x]=v; pre[y]=u;
				opp[u]=v; opp[v]=u;
				continue;
			}
		}
	}
}

int main(){
	int i,j,k,t;
	scanf("%d",&t);
	for(i=1;i<=t;i++){
		init();
		process();
	}
	return 0;
}
