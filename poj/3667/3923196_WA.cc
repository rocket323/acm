#include <iostream>
#define MaxN 50010
using namespace std;

struct node{
	int lmax, rmax, cmax;
	int l, r;
	int flag;
}nd[4*MaxN];

int N, Q;

void build(int now, int a, int b){
	nd[now].l=a; nd[now].r=b;
	
	int mid=(a+b)/2;
	
	nd[now].lmax=nd[now].rmax=nd[now].cmax=(b-a+1);
	nd[now].flag=0;
	if(a<b){
		build(2*now, a, mid);
		build(2*now+1, mid+1, b);
	}
}

int findRoom(int now, int len){
	
	if(nd[now].l==nd[now].r){
		if(nd[now].flag==0)
			return nd[now].l;
		else return 0;
	}
	if(nd[now].cmax<=len&&nd[now].flag==0) return nd[now].l;
	
	if(nd[2*now].cmax>=len){
		return findRoom(2*now, len);
		
	}
	else if(nd[2*now].rmax+nd[now*2+1].lmax>=len){
		return nd[2*now].r+1-nd[2*now].rmax;
	}
	else if(nd[now*2+1].cmax>=len){
		return findRoom(2*now+1, len);
	}
	return 0;
	
}

void flagDown(int now){
	if(nd[now].l==nd[now].r) return;
	if(nd[now].flag==1){
		int lc=now*2, rc=now*2+1;
		nd[lc].flag=1;
		nd[lc].cmax=nd[lc].lmax=nd[lc].rmax=0;
		nd[rc].flag=1;
		nd[rc].cmax=nd[rc].lmax=nd[rc].rmax=0;
	}
	else if(nd[now].flag==0){
		int lc=now*2, rc=now*2+1;
		nd[lc].flag=0;
		nd[lc].cmax=nd[lc].lmax=nd[lc].rmax=(nd[lc].r-nd[lc].l+1);
		nd[rc].flag=0;
		nd[rc].cmax=nd[rc].lmax=nd[rc].rmax=(nd[rc].r-nd[rc].l+1);
	}
}

inline int Max(int a, int b){
	return (a>b)?a:b;
}

void flagUp(int now){
	int lc=now*2, rc=now*2+1;
	if(nd[now].l==nd[now].r) return;
	if(nd[lc].flag==1&&nd[rc].flag==1){
		nd[now].flag=1;
		nd[now].cmax=nd[now].lmax=nd[now].rmax=0;
		return;
	}
	if(nd[lc].flag==0&&nd[rc].flag==0){
		nd[now].flag=0;
		nd[now].cmax=nd[now].lmax=nd[now].rmax=(nd[now].r-nd[now].l+1);
		return;
	}
	nd[now].flag=2;
	nd[now].lmax=nd[lc].lmax;
	if(nd[lc].flag==0)
		nd[now].lmax+=nd[rc].lmax;
		
	nd[now].rmax=nd[rc].rmax;
	if(nd[rc].flag==0)
		nd[now].rmax+=nd[lc].rmax;
	
	nd[now].cmax=Max(nd[lc].cmax, Max(nd[rc].cmax, nd[lc].rmax+nd[rc].lmax));
	
}

void fill(int now, int a, int b){
	if(a<=nd[now].l&&nd[now].r<=b){
		nd[now].lmax=nd[now].rmax=nd[now].cmax=0;
		nd[now].flag=1;
		return;
	}
	flagDown(now);
	
	int mid=(nd[now].l+nd[now].r)/2;
	if(a<=mid) fill(now*2, a, b);
	if(b>mid) fill(now*2+1, a, b);
	
	flagUp(now);	
}

void checkout(int now, int a, int b){
	if(a<=nd[now].l&&nd[now].r<=b){
		nd[now].lmax=nd[now].rmax=nd[now].cmax=(nd[now].r-nd[now].l+1);
		nd[now].flag=0;
		return;
	}
	flagDown(now);
	
	int mid=(nd[now].l+nd[now].r)/2;
	if(a<=mid) checkout(2*now, a, b);
	if(b>mid) checkout(2*now+1, a, b);
	
	flagUp(now);

}

void init(){
	int i,j,k;
	scanf("%d%d", &N, &Q);
	build(1, 1, N);
	
}

void process(){
	int i,j,k, t, a, b;
	for(i=1; i<=Q; ++i){
		scanf("%d", &t);
		if(t==1){
			scanf("%d", &b);
			k=findRoom(1, b);
			printf("%d\n", k);
			if(k!=0)
				fill(1, k, k+b-1);
		}
		else {
			scanf("%d%d", &a, &b);
			checkout(1, a, a+b-1);
		}
	}
}

int main(){
	int i,j,k;
//	freopen("3667.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
