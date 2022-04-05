#include <iostream>
#define MaxN 1001000

using namespace std;

struct node{
	int l, r;
	long long low, high;
}nd[4*MaxN];

struct Message{
	long long low, high;
}msg[MaxN];

long long A[MaxN];
Message tmp;
int N, M;
long long MaxL=200000*200000;

long long Min(long long a, long long b){
	return (a<b)?a:b;
}

long long Max(long long a, long long b){
	return (a>b)?a:b;
}

void build(int now, int l, int r){
	nd[now].l=l; nd[now].r=r;
	if(l==r){
		nd[now].low=nd[now].high=A[l];
	}
	if(l<r){
		int mid=(l+r)>>1;
		build(now*2, l, mid);
		build(now*2+1, mid+1, r);
		nd[now].low=Min(nd[2*now].low, nd[2*now+1].low);
		nd[now].high=Max(nd[2*now].high, nd[2*now+1].high);
	}
}

void init(){
	int i,j,k, t;
	scanf("%d%d", &N, &M);
	for(i=1; i<=N; ++i) scanf("%I64d", &A[i]);
	build(1, 1, N);
}

void query(int now, int l, int r){
	if(l<=nd[now].l&&nd[now].r<=r){
		tmp.low=Min(tmp.low, nd[now].low);
		tmp.high=Max(tmp.high, nd[now].high);
		return;
	}
	int mid=(nd[now].l+nd[now].r)>>1;
	if(l<=mid) query(now*2, l, r);
	if(r>mid) query(now*2+1, l, r);
}

void process(){
	int i,j,k;

	for(i=1; i+M-1<=N; ++i){
		tmp.low=MaxL; tmp.high=-MaxL;
		query(1, i, i+M-1);
		msg[i]=tmp;
	}
	
	for(i=1; i<N+1-M; ++i) printf("%I64d ", msg[i].low);
	printf("%I64d\n", msg[N+1-M].low);
	for(i=1; i<N+1-M; ++i) printf("%I64d ", msg[i].high);
	printf("%I64d\n", msg[N+1-M].high);
}

int main(){
//	freopen("2823.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
