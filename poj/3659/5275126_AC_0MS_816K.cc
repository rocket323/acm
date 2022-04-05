#include <stdio.h>
#include <cstring>
#define MaxL 10000000
#define MaxN 10001
using namespace std;

struct Edge{
	int idx;
	Edge *next;
};

Edge adj[MaxN], memo[2*MaxN+10];
int N, f[MaxN][3], mset=0;
int p[MaxN];
bool vis[MaxN];

void addEdge(int a, int b){
	Edge *ptr=&memo[mset++];
	ptr->idx=b;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void init(){
	int i,j,k,a,b;
	scanf("%d",&N);
	for(i=1;i<N;i++){
		scanf("%d%d",&a,&b);
		addEdge(a, b);
		addEdge(b, a);
	}
	memset(f, -1, sizeof f);
	memset(p, -1, sizeof p);
}

int Min(int a, int b){
	return (a<b)?a:b;
}

int DP(int now, int ty){
	if(f[now][ty]!=-1) return f[now][ty];
	
	
	Edge *ptr;
	bool flag=false;
	int k, ans=0;
	if(ty==0){
		ptr=adj[now].next;
		while(ptr){
			k=ptr->idx;
			if(p[now]==k){ptr=ptr->next; continue; }
			p[k]=now;
			ans+= Min(DP(k,0), Min(DP(k,1), DP(k,2) ) );
			ptr=ptr->next;
			flag=true;
		}
		ans++;
	}
	else if(ty==2){
		ptr=adj[now].next;
		while(ptr){
			k=ptr->idx;
			if(p[now]==k){ptr=ptr->next; continue; }
			p[k]=now;
			ans+= DP(k, 1);
			ptr=ptr->next;
			flag=true;
		}
	}
	else if(ty==1){
		ptr=adj[now].next;
		int sum=0, PP=MaxL;
		while(ptr){
			k=ptr->idx;
			if(p[now]==k){ptr=ptr->next; continue; }
			p[k]=now;
			sum+=Min(DP(k,0), DP(k,1));
			if((-Min(DP(k,0), DP(k,1))+DP(k,0))<PP)
				PP=(-Min(DP(k,0), DP(k,1))+DP(k,0));
			ptr=ptr->next;
			flag=true;
		}
		ans=sum+PP;
	}
	
	if(!flag){
		if(ty==0) return 1;
		if(ty==1) return MaxL;
		if(ty==2) return 0;
	}
	
	f[now][ty]=ans;
	return ans;
}

void process(){
	int i,j,k;
	printf("%d\n",Min(DP(1,0), DP(1, 1)));
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}