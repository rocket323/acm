#include <iostream>
#include <algorithm>
#define MaxN 20008
using namespace std;

struct node{
	int l, r;
	int flag;
}nd[4*MaxN];

int N, p1[MaxN], p2[MaxN], A[MaxN], top, B[MaxN];

void build(int now, int l, int r){
	nd[now].l=l; nd[now].r=r;
	nd[now].flag=0;
	if(l<r){
		int mid=(l+r)>>1;
		build(2*now, l, mid);
		build(2*now+1, mid+1, r);
	}
}

void init(){
	int i,j,k;
	scanf("%d", &N);
	top=0;
	for(i=1; i<=N; ++i){
		scanf("%d%d", &p1[i], &p2[i]);
		A[++top]=p1[i]; A[++top]=p2[i];
	}
	sort(A+1, A+1+2*N);
	B[top=1]=A[1];
	for(i=2; i<=2*N; ++i)
		if(A[i]!=B[top])
			B[++top]=A[i];
	build(1, 1, top);
}

int find(int x){
	int l, r, mid;
	l=1; r=top;
	while(l<=r){
		mid=(l+r)>>1;
		if(B[mid]==x) return mid;
		if(x<B[mid]) r=mid-1;
		else l=mid+1;
	}
}

void flagDown(int now){
	if(nd[now].l==nd[now].r) return;
	if(nd[now].flag){
		nd[2*now].flag=1;
		nd[2*now+1].flag=1;
	}
}

void insert(int now, int l, int r){
	flagDown(now);
	if(l<=nd[now].l&&nd[now].r<=r){
		nd[now].flag=1;
		return;
	}
	int mid=(nd[now].l+nd[now].r)>>1;
	if(l<=mid) insert(2*now, l, r);
	if(r>mid) insert(2*now+1, l, r);
	
	nd[now].flag=nd[2*now].flag&&nd[2*now+1].flag;
}

int getTree(int now, int l, int r){
	flagDown(now);
	
	if(l<=nd[now].l&&nd[now].r<=r){
		return nd[now].flag;
	}
	int mid=(nd[now].l+nd[now].r)>>1;
	int lv=1, rv=1;
	if(l<=mid) lv=getTree(2*now, l, r);
	if(r>mid) rv=getTree(2*now+1, l, r);
	return (lv&&rv);
}	

void process(){
	int i,j,k, a, b, res=0;
	for(i=N; i>=1; --i){
		a=find(p1[i]); b=find(p2[i]);
		k=getTree(1, a, b);
		if(!k) ++res;
		insert(1, a, b);
	}
	printf("%d\n", res);
}

int main(){
	int T;
//	freopen("data.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	scanf("%d", &T);
	while(T--){
		init();
		process();
	}
	return 0;
}
