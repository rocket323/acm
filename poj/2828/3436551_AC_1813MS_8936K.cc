#include <iostream>
#define MaxL 200001
using namespace std;

struct node{
	int l,r;
	int sz;
} nd[4*MaxL];

int n,v[MaxL],p[MaxL],ans[MaxL];

void build(int now, int a, int b){
	nd[now].l=a; nd[now].r=b; nd[now].sz=b-a+1;
	if(a<b){
		int mid=(a+b)>>1;
		build(2*now, a, mid);
		build(2*now+1, mid+1, b);
	}
}

void insert(int now, int p, int v){
	nd[now].sz--;
	if(nd[now].l==nd[now].r){
		ans[nd[now].l]=v;
		return;
	}
	if(nd[2*now].sz>=p) insert(2*now, p, v);
	else insert(2*now+1, p-nd[2*now].sz, v);
}

void init(){
	int i,j,k;
	build(1,1,n);
	for(i=1;i<=n;i++)
		scanf("%d%d",&p[i],&v[i]);
}

void process(){
	int i,j,k;
	for(i=n;i>0;i--)
		insert(1,p[i]+1,v[i]);
	for(i=1;i<n;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
}

int main(){
	int i,j,k;
	while(cin>>n){
		init();
		process();
	}
	return 0;
}
	
