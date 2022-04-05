#include <iostream>
#define MaxN 50000
#include <algorithm>
using namespace std;

struct node{
	long long l, r;
	long long MaxH;
}nd[8*MaxN];

struct build{
	long long lnum, rnum, h;
	long long lv, rv;
}H[MaxN];

long long A[2*MaxN], B[2*MaxN], N, cnt;

long long find(long long x){
	long long l=1, r=cnt, mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(B[mid]==x) return mid;
		if(x>B[mid]) l=mid+1;
		else r=mid-1;
	}
}

void build(long long now, long long l, long long r){
	nd[now].l=l; nd[now].r=r; nd[now].MaxH=0;
	if(r-l>1){
		long long mid=(l+r)>>1;
		build(now*2, l, mid);
		build(now*2+1, mid, r);
	}
}

long long Max(long long a, long long b){
	return (a>b)?a:b;
}

void insert(long long now, long long l, long long r, long long h){
	if(l<=nd[now].l&&nd[now].r<=r){
		nd[now].MaxH=Max(nd[now].MaxH, h);
		return;
	}
	long long mid=(nd[now].l+nd[now].r)>>1;
	if(l<mid) insert(now*2, l, r, h);
	if(r>mid) insert(now*2+1, l, r, h);
}

void flagDown(long long now){
	nd[2*now].MaxH = Max(nd[2*now].MaxH, nd[now].MaxH);
	nd[2*now+1].MaxH = Max(nd[2*now+1].MaxH, nd[now].MaxH);
}

long long getTree(long long now, long long l, long long r){
	if(l<=nd[now].l&&nd[now].r<=r){
		return nd[now].MaxH;
	}
	flagDown(now);
	long long mid=(nd[now].l + nd[now].r)>>1;
	long long lv=0, rv=0;
	if(l<mid) lv=getTree(now*2, l, r);
	if(r>mid) rv=getTree(now*2+1, l, r);
	return Max(lv, rv);
}

void init(){
	long long i,j,k=0;
	cnt=1;
	scanf("%I64d", &N);
	for(i=1; i<=N; ++i){
		scanf("%I64d%I64d%I64d", &H[i].lnum, &H[i].rnum, &H[i].h);
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
	long long i,j,k;
	long long ans=0;
	build(1, 1, cnt);
	for(i=1; i<=N; ++i) insert(1, H[i].lv, H[i].rv, H[i].h);
	for(i=1; i<cnt; ++i){
		ans+=(B[i+1]-B[i])*getTree(1, i, i+1);
		
	}
	printf("%I64d\n", ans);
}

int main(){

	init();
	process();

	return 0;
}
