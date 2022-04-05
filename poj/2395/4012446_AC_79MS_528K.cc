#include <iostream>
#include <algorithm>
#define MaxL 2000000000
using namespace std;

struct Edge{
	int a, b, len;
}E[10001];

int cmp(Edge A, Edge B){
	return (A.len<B.len);
}

int N, M, pre[2008];

int init(){
	int i,j,k;
	scanf("%d%d", &N, &M);
	for(i=0; i<M; ++i) {
		scanf("%d%d%d", &E[i].a, &E[i].b, &E[i].len);
	}
	sort(E, E+M, cmp);
}

int find(int now){
	if(pre[now]==now) return now;
	int ans=find(pre[now]);
	pre[now]=ans;
	return ans;
}

bool kruskal(int check){
	int i,j,k, x, y, cnt=0;
	for(i=1; i<=N; i++) pre[i]=i;
	for(i=0; i<M; ++i){
		if(E[i].len>check) continue;
		x=find(E[i].a); y=find(E[i].b);
		if(x==y) continue;
		pre[x]=y;
		cnt++;
		if(cnt==N-1) break;
	}
	if(cnt==N-1) return true;
	return false;
}

int Min(int a, int b){
	return (a<b)?a:b;
}

void process(){
	int i,j,k, l, r, mid, ans=MaxL;
	l=0; r=MaxL/2;
	while(l<=r){
		mid=(l+r)/2;
		if(kruskal(mid)){
			ans=Min(ans, mid);
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d\n", ans);
}

int main(){
	int i,j,k;
	init();
	process();
	return 0;
}
