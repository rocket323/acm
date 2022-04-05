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

int A[MaxN];
int N, M;
long long MaxL=200000*200000;

int Min(int a, int b){
	return (a<b)?a:b;
}

int Max(int a, int b){
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
	for(i=1; i<=N; ++i) scanf("%d", &A[i]);
	build(1, 1, N);
}

Message query(int now, int l, int r){
	Message msg;
	if(l<=nd[now].l&&nd[now].r<=r){
		msg.low=nd[now].low; msg.high=nd[now].high;
		return msg;
	}
	Message t1, t2;
	t1.low=t2.low=MaxL;
	t1.high=t2.high=-MaxL;
	int mid=(nd[now].l+nd[now].r)>>1;
	if(l<=mid) t1=query(now*2, l, r);
	if(r>mid) t2=query(now*2+1, l, r);
	msg.low=Min(t1.low, t2.low);
	msg.high=Max(t1.high, t2.high);
	return msg;
}

void process(){
	int i,j,k;

	for(i=1; i+M-1<=N; ++i) msg[i]=query(1, i, i+M-1);
	
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
