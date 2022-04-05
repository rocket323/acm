#include <iostream>
#define MaxN 100100
using namespace std;

struct node{
	long long l, r, sum;
	long long flag;
}nd[6*MaxN];

long long N, M, A[MaxN];

void build(long long now, long long l, long long r){
	nd[now].l=l; nd[now].r=r; nd[now].flag=0;
	if(l==r) nd[now].sum=A[l];
	if(l<r){
		long long mid=(l+r)>>1;
		build(now*2, l, mid);
		build(now*2+1, mid+1, r);
		nd[now].sum=nd[now*2].sum + nd[now*2+1].sum;
	}
}

void flagDown(long long now){
	long long l=now*2;
	long long r=l+1;
	if(nd[now].l==nd[now].r) return;
	if(nd[now].flag!=0){
		if(nd[l].flag!=0) flagDown(l);
		if(nd[r].flag!=0) flagDown(r);
		nd[l].sum+=(nd[l].r-nd[l].l+1)*nd[now].flag;
		nd[r].sum+=(nd[r].r-nd[r].l+1)*nd[now].flag;
		nd[l].flag=nd[r].flag=nd[now].flag;
		nd[now].flag=0;
	}
}

void add(long long now, long long l, long long r, long long c){
	flagDown(now);

	if(l<=nd[now].l&&nd[now].r<=r){
		nd[now].sum+=(nd[now].r-nd[now].l+1)*c;
		nd[now].flag=c;
		return;
	}
	long long mid=(nd[now].l+nd[now].r)>>1;
	if(l<=mid) add(now*2, l, r, c);
	if(r>mid) add(now*2+1, l, r, c);
	nd[now].sum=nd[2*now].sum+nd[2*now+1].sum;
}

long long query(long long now, long long l, long long r){
	if(l<=nd[now].l&&nd[now].r<=r){
		return nd[now].sum;
	}
	flagDown(now);
	long long lv=0, rv=0;
	long long mid=(nd[now].l+nd[now].r)>>1;
	if(l<=mid) lv=query(now*2, l, r);
	if(r>mid) rv=query(now*2+1, l, r);
	return lv+rv;
}		

void init(){
	long long i,j,k;
	scanf("%I64d%I64d", &N, &M);
	for(i=1; i<=N; ++i) scanf("%I64d", &A[i]);
	build(1, 1, N);
}

void process(){
	long long i,j,k, a, b, c;
	char S[10];
	for(i=1; i<=M; ++i){
		scanf("%s", S);
		if(S[0]=='Q'){
			scanf("%I64d%I64d", &a, &b);
			printf("%I64d\n", query(1, a, b));
		}
		else {
			scanf("%I64d%I64d%I64d", &a, &b, &c);
			add(1, a, b, c);
		}
	}
}

int main(){
//	freopen("3468.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
