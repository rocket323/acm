#include <iostream>
#define MaxN 40010
using namespace std;

struct Edge{
	int idx, w;
	Edge *next;
};

Edge adj[MaxN+10], memo[2*MaxN+10];

int N, M, Q, P[MaxN][20], mset;
int L[MaxN], T[MaxN], d[MaxN];

void dfs(int now, int len, int dep){
	d[now]=len; L[now]=dep;
	Edge *ptr=adj[now].next;
	while(ptr){
		int k=ptr->idx;
		if(T[now]!=k){
			T[k]=now;
			dfs(k, len+ptr->w, dep+1);
		}
		ptr=ptr->next;
	}
}

void addEdge(int a, int b, int w){
	Edge *ptr=&memo[mset++];
	ptr->idx=b;
	ptr->w=w;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void init(){
	int i,j,k, a,b,w;
	char ch;
	cin>>N>>M;
	mset=0;
	for(i=0;i<N;i++) adj[i].next=NULL;
	for(i=1;i<=M;i++){
		cin>>a>>b>>w>>ch;
	//	cout<<a<<' '<<b<<' '<<w<<' '<<ch<<endl;
		addEdge(a-1, b-1, w);
		addEdge(b-1, a-1, w);
	}
	memset(T, -1, sizeof T);
	dfs(0, 0, 0);
	
	memset(P, -1, sizeof P);
	for(i=0;i<N;i++)
		P[i][0]=T[i];
	for(j=1;(1<<j)<N;j++)
		for(i=0;i<N;i++)
			if(P[i][j-1]!=-1)
				P[i][j]=P[P[i][j-1]][j-1];
}

int LCA(int a, int b){
	int i,j,k, tmp, log;
	
	if(L[a]<L[b]){
		tmp=a; a=b; b=tmp;
	}
	
	for(log=1;1<<log<=L[a];log++);
	log--;
	
	for(i=log; i>=0; i--)
		if(L[a]-(1<<i)>=L[b])
			a=P[a][i];
	
	if(a==b) return a;
	
	for(i=log; i>=0; i--)
		if(P[a][i]!=-1&&P[a][i]!=P[b][i]){
			a=P[a][i];
			b=P[b][i];
		}
		
	return T[a];
}

void process(){
	int i,j,k, a, b, ans;
	cin>>Q;
	for(i=1;i<=Q;i++){
		cin>>a>>b;
		k=LCA(a-1, b-1);
	//	cout<<a<<' '<<b<<' '<<k+1<<endl;
	//	cout<<d[a-1]<<' '<<d[b-1]<<' '<<d[k]<<endl;
		ans=d[a-1]+d[b-1]-2*d[k];
		cout<<ans<<endl;
	}
}

int main(){
	int i,j,k;
//	freopen("dquery.4.in","r",stdin);
//	freopen("1986.out","w",stdout);
	init();
	process();
//	while(k=1);
	return 0;
}
