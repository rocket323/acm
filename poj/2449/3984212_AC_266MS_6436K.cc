#include <iostream>
#define MaxN 1010
#define MaxM 100010
#define MaxL 100000000
using namespace std;

struct Node{
	int val, idx;
}H[2000*MaxN];

struct Edge{
	int idx, cost;
	Edge *next;
};
Edge adj[MaxN], memo[MaxM*4], adj2[MaxN];
int mset, ans;

int N, M, S, T, K, size;
int vis[MaxN], dist[MaxN];

void addEdge(Edge G[], int a, int b, int c){
	Edge* ptr=&memo[mset++];
	ptr->idx=b;
	ptr->cost=c;
	ptr->next=G[a].next;
	G[a].next=ptr;
}

void swap(int i, int j){
	Node tmp;
	tmp=H[i]; H[i]=H[j]; H[j]=tmp;
}

Node pop(){
	int i,j,k, t;
	Node ans=H[1];
	H[1]=H[size];
	size--;
	k=1;
	while(k<size){
		i=2*k; j=i+1;
		if(i>size) break;
		if(j>size) t=i;
		else {
			if(H[i].val<H[j].val) t=i;
			else t=j;
		}
		if(H[k].val>H[t].val){
			swap(k, t);
			k=t;
		}
		else break;
	}
	return ans;
}

void push(int idx, int val){
	int i,j,k, mid;
	size++;
	H[size].idx=idx; H[size].val=val;
	k=size;
	while(k>1){
		mid=k/2;
		if(H[k].val<H[mid].val){
			swap(k, mid);
			k=mid;
		}
		else break;
	}
}

void dijkstra(int source){
	int i,j,k, Min, rec, p;
	Node tmp;
	Edge *ptr;
	memset(vis, 0, sizeof vis);
	for(i=0; i<N; ++i) dist[i]=MaxL;
	size=0;
	dist[source]=0;
	push(source, 0);
	
	for(i=1; i<N; i++){
		tmp=pop();
		k=tmp.idx; rec=tmp.val;
		ptr=adj2[k].next;
		while(ptr){
			p=ptr->idx;
			if(dist[k]+ptr->cost<dist[p]){
				dist[p]=dist[k]+ptr->cost;
				push(p, dist[k]+ptr->cost);
			}
			ptr=ptr->next;
		}
	}
}

void init(){
	int i,j,k, a, b, c;
	for(i=0; i<N; ++i){
		adj[i].next=NULL;
		adj2[i].next=NULL;
	}
	mset=0;
	for(i=0; i<M; ++i){
		scanf("%d%d%d", &a, &b, &c);
		addEdge(adj, a-1, b-1, c);
		addEdge(adj2, b-1, a-1, c);
	}
	scanf("%d%d%d", &S, &T, &K);
	--S; --T;
	if(S==T) K++;
	dijkstra(T);
}

void process(){
	int i,j,k, p;
	Node tmp;
	Edge* ptr;
	memset(vis, 0, sizeof vis);
	size=0;
	push(S, dist[S]);
	while(size>0){
		tmp=pop(); k=tmp.idx;
		vis[k]++;
		if(k==T&&vis[k]==K){
			printf("%d\n", tmp.val);
			return;
		}
		ptr=adj[k].next;
		while(ptr){
			p=ptr->idx;
			push(p, tmp.val - dist[k] + ptr->cost + dist[p]);
			ptr=ptr->next;
		}
	}
	printf("-1\n");
}

int main(){
	int i,j,k;
//	freopen("2449.in", "r", stdin);
	while(scanf("%d%d", &N, &M)!=EOF){	
		init();
		process();
	}
//	while(1);
	return 0;
}
