#include <iostream>
#define MaxN 100100
using namespace std;

struct node{
	int l, r;
	long long sum;
	long long flag;
}nd[6*MaxN];

int N, M, A[MaxN];

void build(int now, int l, int r){
	nd[now].l=l; nd[now].r=r; nd[now].flag=0;
	if(l==r) nd[now].sum=A[l];
	if(l<r){
		int mid=(l+r)>>1;
		build(now<<1, l, mid);
		build((now<<1)+1, mid+1, r);
		nd[now].sum=nd[now*2].sum + nd[now*2+1].sum;
	}
}

void flagDown(int now){
	int l=now<<1;
	int r=l+1;
	if(nd[now].l==nd[now].r) return;
	if(nd[now].flag!=0){
		nd[l].sum+=(nd[l].r-nd[l].l+1)*nd[now].flag;
		nd[r].sum+=(nd[r].r-nd[r].l+1)*nd[now].flag;
		nd[l].flag+=nd[now].flag;
		nd[r].flag+=nd[now].flag;
		nd[now].flag=0;
	}
}

void add(int now, int l, int r, int c){
	flagDown(now);

	if(l<=nd[now].l&&nd[now].r<=r){
		nd[now].sum+=(nd[now].r-nd[now].l+1)*c;
		nd[now].flag=c;
		return;
	}
	int mid=(nd[now].l+nd[now].r)>>1;
	if(l<=mid) add(now<<1, l, r, c);
	if(r>mid) add((now<<1)+1, l, r, c);
	nd[now].sum=nd[2*now].sum+nd[2*now+1].sum;
}

long long query(int now, int l, int r){
	flagDown(now);
        if(l<=nd[now].l&&nd[now].r<=r){
		return nd[now].sum;
	}
	
	long long lv=0, rv=0;
	int mid=(nd[now].l+nd[now].r)>>1;
	if(l<=mid) lv=query(now<<1, l, r);
	if(r>mid) rv=query((now<<1)+1, l, r);
	return lv+rv;
}		

void init(){
	int i,j,k;
	scanf("%d%d", &N, &M);
	for(i=1; i<=N; ++i) scanf("%d", &A[i]);
	build(1, 1, N);
}

void process(){
	int i,j,k, a, b, c;
	char S[10];
	for(i=1; i<=M; ++i){
		scanf("%s", S);
		if(S[0]=='Q'){
			scanf("%d%d", &a, &b);
			printf("%I64d\n", query(1, a, b));
		}
		else {
			scanf("%d%d%d", &a, &b, &c);
			add(1, a, b, c);
		}
	}
}

int main(){

	init();
	process();
	return 0;
}