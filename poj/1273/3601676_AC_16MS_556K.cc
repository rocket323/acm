#include <iostream>
#define MaxL 1000000000
using namespace std;

int N,M,G[201][201],pre[201],lt[201];
int Q[301],head, tail;

void init(){
	int i,j,k,a,b,c;
	memset(G,0,sizeof G);
	for(i=1;i<=M;i++){
		scanf("%d%d%d",&a,&b,&c);
		G[a][b]+=c;
	}
}

bool bfs(){
	int i,j,k;
	memset(lt,0,sizeof lt);
	head=1; tail=1; Q[1]=1; lt[1]=1;
	while(head<=tail){
		k=Q[head];
		for(i=1;i<=N;i++)
			if(lt[i]==0&&G[k][i]>0){
				tail++;
				Q[tail]=i;
				lt[i]=1;
				pre[i]=k;
			}
		head++;
	}
	if(lt[N]!=0) return true;
	else return false;
}

int MinN(int a, int b){
	return (a>b)?b:a;
}

void maxFlow(){
	int i,j,k,arg,ans=0,Min;
	while(bfs()){
		k=N; Min=MaxL;
		while(k!=1){
			Min=MinN(Min,G[pre[k]][k]);
			k=pre[k];
		}
		ans+=Min;
		k=N;
		while(k!=1){
			G[pre[k]][k]-=Min;
			G[k][pre[k]]+=Min;
			k=pre[k];
		}
	}
	printf("%d\n",ans);
}

int main(){
	int i,j,k;
//	freopen("1273.in","r",stdin);
	while(scanf("%d%d",&M,&N)!=EOF){
		init();
		maxFlow();
	}
//	while(k=1);
	return 0;
}
