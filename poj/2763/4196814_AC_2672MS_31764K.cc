#include <iostream>
#define MaxN 200020
using namespace std;

struct node{
	int l, r;
	int d, buf;
}nd[4*MaxN];

struct Edge{
	int idx, dist;
	Edge* next;
};

Edge adj[MaxN], memo[MaxN];

int N, Q, pos, p[MaxN], s[MaxN], t[MaxN], id, mset;
int A[MaxN], B[MaxN], C[MaxN];
int L[MaxN], f[MaxN][20], rt;

void dfs(int now, int lev){
	s[now]=id++; L[now]=lev;
	Edge* ptr=adj[now].next;
	while(ptr){
		int k=ptr->idx;
		if(p[now]!=k){
			p[k]=now;
			dfs(k, lev+1);
		}
		ptr=ptr->next;
	}
	t[now]=id++;
}

void addEdge(int a, int b, int c){
	Edge* ptr=&memo[mset++];
	ptr->idx=b; ptr->dist=c;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void init(){
	int i,j,k, a, b, c;
//	scanf("%d%d%d", &N, &Q, &pos);
	for(i=0; i<=N; ++i) adj[i].next=NULL;
	memset(p, -1, sizeof p);
	for(i=1; i<N; ++i){
		scanf("%d%d%d", &a, &b, &c);
		A[i]=a; B[i]=b; C[i]=c;
	//	p[b]=a;
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
	id=1;
//	for(i=1; i<=N; ++i)
//		if(p[i]==-1){
			rt=1;
			dfs(1, 0);
//			break;
	//	}
		
	for(i=1; i<N; ++i)
		if(p[A[i]]==B[i]){
			int tmp=A[i]; A[i]=B[i]; B[i]=tmp;
		}
		
}

void build(int now, int l, int r){
	nd[now].l=l; nd[now].r=r; nd[now].d=nd[now].buf=0;
	if(l<r){
		int mid=(l+r)>>1;
		build(2*now, l, mid);
		build(2*now+1, mid+1, r);
	}
}

void flagDown(int now){
	if(nd[now].l==nd[now].r) return;
	int l=2*now, r=2*now+1;
	int ls=nd[l].r-nd[l].l+1, rs=nd[r].r-nd[r].l+1;
	nd[l].d+=ls*nd[now].buf;
	nd[l].buf+=nd[now].buf;
	nd[r].d+=rs*nd[now].buf;
	nd[r].buf+=nd[now].buf;
	nd[now].buf=0;
}

int getTree(int now, int l, int r){
	flagDown(now);
	if(l<=nd[now].l&&nd[now].r<=r){
		return nd[now].d;
	}
	int lv=0, rv=0;
	int mid=(nd[now].l+nd[now].r)>>1;
	if(l<=mid) lv=getTree(2*now, l, r);
	if(r>mid) rv=getTree(2*now+1, l, r);
	return lv+rv;
}

void change(int now, int l, int r, int add){
	flagDown(now);
	if(l<=nd[now].l&&nd[now].r<=r){
		nd[now].d+=(nd[now].r-nd[now].l+1)*add;
		nd[now].buf+=add;
		return;
	}
	int mid=(nd[now].l+nd[now].r)>>1;
	if(l<=mid) change(2*now, l, r, add);
	if(r>mid) change(2*now+1, l, r, add);
}

void LCA_ready(){
	int i,j,k;
	memset(f, -1, sizeof f);
	for(i=1; i<=N; ++i) f[i][0]=p[i];
	for(j=1; (1<<j)<=N; ++j)
		for(i=1; i<=N; ++i)
			if(f[i][j-1]!=-1)
				f[i][j]=f[f[i][j-1]][j-1];
}

int LCA(int a, int b){
	int i,j,k, log, tmp;
	if(L[a]<L[b]){ tmp=a; a=b; b=tmp; }
	for(log=1; (1<<log)<=L[a]; ++log);
	--log;
	for(i=log; i>=0; --i)
		if(L[a]-(1<<i)>=L[b]){
			a=f[a][i];
		}
	
	if(a==b) return a;
	
	for(i=log; i>=0; --i)
		if(f[a][i]!=-1&&f[a][i]!=f[b][i]){
			a=f[a][i]; b=f[b][i];
		}
	
	return p[a];
}	

void process(){
	int i,j,k, a, b, c, d1, d2, d3;

	build(1, s[rt], t[rt]);
	
	LCA_ready();

	for(i=1; i<N; ++i){
		change(1, s[B[i]], t[B[i]], C[i]);
	}
	
	for(i=1; i<=Q; ++i){
		scanf("%d", &k);
		if(k==0){
			scanf("%d", &a);
			b=LCA(pos, a);
			
			d1=getTree(1, t[pos], t[pos]);
			d2=getTree(1, t[a], t[a]);
			d3=getTree(1, t[b], t[b]);
			printf("%d\n", d1+d2-2*d3);
			pos=a;
		}
		else{
			scanf("%d%d", &a, &c);
			change(1, s[B[a]], t[B[a]], c-C[a]);
			C[a]=c;
		}
	}
}

int main(){
//	freopen("2763.in", "r", stdin);
	while(scanf("%d%d%d", &N, &Q, &pos)!=EOF){
		init();
		process();
	}
//	while(1);
	return 0;
}
