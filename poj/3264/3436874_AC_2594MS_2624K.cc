#include <iostream>
#define MM 100000000
#define MaxL 50001
using namespace std;

struct node{
	int Max, Min;
	int l, r;
} nd[4*MaxL];

int n,h[MaxL],q;

void build(int now, int a, int b){
	nd[now].l=a; nd[now].r=b;
	nd[now].Max=0; nd[now].Min=0;
	if(a<b){
		int mid=(a+b)>>1;
		build(2*now, a, mid);
		build(2*now+1, mid+1, b);
	}
}

void update(int now){
	int lc,rc;
	lc=2*now; rc=lc+1;
	nd[now].Max=(nd[lc].Max>nd[rc].Max) ? nd[lc].Max : nd[rc].Max;
	nd[now].Min=(nd[lc].Min<nd[rc].Min) ? nd[lc].Min : nd[rc].Min;
}

void insert(int now, int a, int b, int h){
	if(a<=nd[now].l&&nd[now].r<=b){
		nd[now].Max=h; nd[now].Min=h;
		return;
	}
	int mid=(nd[now].l+nd[now].r)>>1;
	if(a<=mid) insert(2*now, a, b, h);
	if(b>mid) insert(2*now+1,a, b, h);
	update(now);
}

int get1(int now, int a, int b){
	if(a<=nd[now].l&&nd[now].r<=b)
		return nd[now].Max;
	int lv=0, rv=0;
	int mid=(nd[now].l+nd[now].r)>>1;
	if(a<=mid) lv=get1(2*now, a, b);
	if(b>mid) rv=get1(2*now+1, a, b);
	return (lv>rv)?lv:rv;
}

int get2(int now, int a, int b){
	if(a<=nd[now].l&&nd[now].r<=b)
		return nd[now].Min;
	int lv=MM, rv=MM;
	int mid=(nd[now].l+nd[now].r)>>1;
	if(a<=mid) lv=get2(2*now, a, b);
	if(b>mid) rv=get2(2*now+1, a, b);
	return (lv<rv)?lv:rv;
}

int main(){
	int i,j,k,a,b,ans;
	scanf("%d%d",&n,&q);
	build(1,1,n);
	for(i=1;i<=n;i++){
		scanf("%d",&h[i]);
		insert(1,i,i,h[i]);
	}
	for(i=1;i<=q;i++){
		scanf("%d%d",&a,&b);
		ans=get1(1,a,b)-get2(1,a,b);
		printf("%d\n",ans);
	}
	return 0;
}
	
	
	
