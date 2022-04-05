#include <iostream>
#define MaxN 50000
#include <algorithm>
using namespace std;

struct node{
	int l, r;
	int MaxH;
}nd[4*MaxN];

struct build{
	int lnum, rnum, h;
	int lv, rv;
}H[MaxN];

int A[MaxN], B[MaxN], N, cnt;

int find(int x){
	int l=1, r=cnt, mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(B[mid]==x) return mid;
		if(x>B[mid]) l=mid+1;
		else r=mid-1;
	}
}

void build(int now, int l, int r){
	nd[now].l=l; nd[now].r=r; nd[now].MaxH=0;
	if(r-l>1){
		int mid=(l+r)>>1;
		build(now*2, l, mid);
		build(now*2+1, mid, r);
	}
}

int Max(int a, int b){
	return (a>b)?a:b;
}

void insert(int now, int l, int r, int h){
	if(l<=nd[now].l&&nd[now].r<=r){
		nd[now].MaxH=Max(nd[now].MaxH, h);
		return;
	}
	int mid=(nd[now].l+nd[now].r)>>1;
	if(l<mid) insert(now*2, l, r, h);
	if(r>mid) insert(now*2+1, l, r, h);
}

void flagDown(int now){
	nd[2*now].MaxH = Max(nd[2*now].MaxH, nd[now].MaxH);
	nd[2*now+1].MaxH = Max(nd[2*now+1].MaxH, nd[now].MaxH);
}

int getTree(int now, int l, int r){
	if(l<=nd[now].l&&nd[now].r<=r){
		return nd[now].MaxH;
	}
	flagDown(now);
	int mid=(nd[now].l + nd[now].r)>>1;
	int lv=0, rv=0;
	if(l<mid) lv=getTree(now*2, l, r);
	if(r>mid) rv=getTree(now*2+1, l, r);
	return Max(lv, rv);
}

void init(){
	int i,j,k=0;
	cnt=1;
	scanf("%d", &N);
	for(i=1; i<=N; ++i){
		scanf("%d%d%d", &H[i].lnum, &H[i].rnum, &H[i].h);
		A[++k]=H[i].lnum; A[++k]=H[i].rnum;
	}
	sort(A+1, A+1+2*N);
	B[1]=A[1];
	for(i=2; i<=2*N; ++i){
		if(A[i]!=B[cnt])
			B[++cnt]=A[i];
	}
	for(i=1; i<=N; ++i){
		H[i].lv=find(H[i].lnum);
		H[i].rv=find(H[i].rnum);
	}
}

void process(){
	int i,j,k, ans=0;
	build(1, 1, cnt);
	for(i=1; i<=N; ++i) insert(1, H[i].lv, H[i].rv, H[i].h);
	for(i=1; i<cnt; ++i){
		ans+=(B[i+1]-B[i])*getTree(1, i, i+1);
		
	}
	printf("%d\n", ans);
}

int main(){
//	freopen("3277.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
