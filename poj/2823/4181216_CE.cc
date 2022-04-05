#include <iostream>
using namespace std;

struct node{
	int l, r;
	int low, high;
}nd[4*MaxN];

struct Message{
	int low, high;
}msg[MaxN];

long long A[MaxN];
Message tmp;
int N, M, lv, hv;
long long low, high;

void build(int now, int l, int r){
	nd[now].l=l; nd[now].r=r;
	if(l==r){
		nd[now].low=nd[now].high=l;
	}
	if(l<r){
		int mid=(l+r)>>1;	
		build(now*2, l, mid);
		build(now*2+1, mid+1, r);
		if(A[nd[now*2].low]<A[nd[2*now+1].low]) nd[now].low=nd[2*now].low;
		else nd[now].low=nd[2*now+1].low;
		
		if(A[nd[now*2].high]>A[nd[2*now+1].high]) nd[now].high=nd[2*now].high;
		else nd[now].high=nd[2*now+1].high;
	}
}

void init(){
	int i,j,k, t;
	hv=lv=0;
	
	for(i=1; i<=N; ++i){
		scanf("%I64d", &A[i]);
	//	cout<<A[i]<<endl;
		if(i==1){
			lv=hv=1; high=low=A[i];
		}
		else{
			if(A[i]>high){ hv=i; high=A[i]; }
			if(A[i]<low) { lv=i; low=A[i]; }
		}
	}
	build(1, 1, N);
}

void query(int now, int l, int r){
	if(l<=nd[now].l&&nd[now].r<=r){
		if(A[nd[now].low]<A[tmp.low]) tmp.low=nd[now].low;
		if(A[nd[now].high]>A[tmp.high]) tmp.high=nd[now].high;
		return;
	}
	int mid=(nd[now].l+nd[now].r)>>1;
	if(l<=mid) query(now*2, l, r);
	if(r>mid) query(now*2+1, l, r);
}

void process(){
	int i,j,k;
	for(i=1; i+M-1<=N; ++i){
		tmp.low=hv; tmp.high=lv;
		query(1, i, i+M-1);
		msg[i]=tmp;
	}
	
	for(i=1; i<N+1-M; ++i) printf("%I64d", A[msg[i].low]);
	printf("%I64d", A[msg[N+1-M].low]);
	for(i=1; i<N+1-M; ++i) printf("%I64d", A[msg[i].high]);
	printf("%I64d", A[msg[N+1-M].high]);
}

int main(){
//	freopen("2823.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	while(scanf("%d%d", &N, &M)!=EOF){
		init();
		process();
	}
//	while(1);
	return 0;
}