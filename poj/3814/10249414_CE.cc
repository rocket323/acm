#include <iostream>
#include <stdio.h>
#include <cstring>
#define MaxN 501
#define MaxL 10000000
using namespace std;

struct Edge{
	int idx, flow;
	Edge* next;
	Edge* opp;
};
Edge adj[MaxN], memo[400*MaxN];

int N, M, mset=0, Path[MaxN], top, n;
int Q[MaxN], Lv[MaxN], s, t;
Edge *pre[MaxN], *cur[MaxN];

void addEdgeProcess(int a, int b, int c){
	Edge* ptr=&memo[mset++];
	ptr->idx=b; ptr->flow=c;
	ptr->next=adj[a].next;
	adj[a].next=ptr;
}

void addEdge(int a, int b, int c){
	addEdgeProcess(a, b, c);
	addEdgeProcess(b, a, 0);
	adj[a].next->opp=&memo[mset-1];
	adj[b].next->opp=&memo[mset-2];
}

int min(int a, int b){
	return (a<b)?a:b;
}

bool bfs(int S, int T){
	int head, tail;
	Edge* ptr;
	memset(Lv, -1, sizeof Lv);
	Q[head=tail=1]=S; Lv[S]=0;
	while(head<=tail){
		int k=Q[head];
		ptr=adj[k].next;
		while(ptr){
			int p=ptr->idx;
			if(Lv[p]==-1&&ptr->flow>0){
				Lv[p]=Lv[k]+1;
				Q[++tail]=p;
			}
			ptr=ptr->next;
		}
		head++;
	}
	return (Lv[T]!=-1);
}	

int Dinic(int S, int T){
	int i,j,k, flow=0, Min, u, v;
	while(bfs(S, T)){
		top=1; Path[top]=u=S;
		for(i=S; i<=T; ++i) cur[i]=adj[i].next;
		while(cur[S]){
			if(u!=T&&cur[u]&&cur[u]->flow>0&&Lv[cur[u]->idx]==Lv[u]+1){
				top++; v=cur[u]->idx;
				Path[top]=v;
				pre[v]=cur[u];
				u=v;
			}
			else if(u==T){
				Min=MaxL;
				for(i=top; i>1; --i) Min=min(Min, pre[Path[i]]->flow);
				for(i=top; i>1; --i){
					pre[Path[i]]->flow-=Min;
					pre[Path[i]]->opp->flow+=Min;
					if(pre[Path[i]]->flow==0) top=i-1;
				}
				u=Path[top];
				flow+=Min;
			}
			else {
				while(u!=S&&cur[u]==NULL) u=Path[--top];
				cur[u]=cur[u]->next;
			}
		}
	}
	return flow;
}

int calc(int sa, int x) {
	int a = sa / 60;
	int b = sa % 60;
	if(b == 30) return 2 * a + 1;
	if(b == 0) return 2 * a;
	if(b > 30) {
		if(x) b = 1;
		else {
			a = (a + 1) % 24;
			//a++;
			b = 0;
		}
	}
	else if(b > 0) {
		if(x) b = 0;
		else {
			b = 1;
		}
	}
	return 2 * a + b;
}

int a[100][100], b[100][100], k[100], l[100];
bool can_m[51][1550], can[51][50];
int sa[100][100], sb[100][100];

bool check(int cover) {
	mset = 0;
	for(int i=s; i<=t; ++i) adj[i].next = NULL;
	for(int i=0; i<48; ++i) {
		addEdge(s, i + 1, cover);
	}
	for(int i=0; i<n; ++i) {
		addEdge(48 + i + 1, t, l[i] / 30);
		for(int j=0; j<48; ++j) {
			if(can[i][j]) addEdge(j + 1, i + 48 + 1, 1);
		}
	}
	int flow = Dinic(s, t);
	return flow == cover * 48;
}

int main() {
	while(scanf("%d", &n), n) {
		s = 0, t = 48 + n + 1;
		N = n;

		memset(can_m, 0, sizeof can_m);
		memset(can, 0, sizeof can);
		char ss[100], tt[100];
		for(int i=0; i<n; ++i) {
			scanf("%d%d", &k[i], &l[i]);
			for(int j=0; j<k[i]; ++j) {
				scanf("%s%s", ss, tt);
				sa[i][j] = ((ss[0] - '0') * 10 + ss[1] - '0') * 60 + (ss[3] - '0') * 10 + (ss[4] - '0');
				sb[i][j] = ((tt[0] - '0') * 10 + tt[1] - '0') * 60 + (tt[3] - '0') * 10 + (tt[4] - '0');

				if(sa[i][j] == sb[i][j]) {
					for(int x=0; x<1440; ++x) can_m[i][x] = 1;
				}
				else if(sa[i][j] < sb[i][j]) {
					for(int x=sa[i][j]; x<sb[i][j]; ++x) can_m[i][x] = 1;
				}
				else {
					for(int x=sa[i][j]; x<1440; ++x) can_m[i][x] = 1;
					for(int x=0; x<sb[i][j]; ++x) can_m[i][x] = 1;
				}
			}
		}

		for(int i=0; i<n; ++i) {
			for(int j=0; j<48; ++j) {
				can[i][j] = 1;
				int p = j * 30;
				for(int c=0; c<30; ++c) {
					if(!can_m[i][p+c]) can[i][j] = 0;
				}
			}
		}

		int left = 0, right = n, mid;
		while(left <= right) {
			mid = (left + right) / 2;
			if(check(mid)) {
				ans = mid;
				left = mid + 1;
			}
			else right = mid - 1;
		}

		printf("%d\n", ans);
	}
	return 0;
}
