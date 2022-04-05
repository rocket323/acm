#include <iostream>
#define MaxL 500010
using namespace std;
struct node{
	long long l,r;
	long long sum;
}nd[4*MaxL];

long long n,pos[MaxL],rank[MaxL],a[MaxL];

void qsort(long long s,long long t){
	long long x,i,j,k;
	x=a[pos[(s+t)/2]];
	i=s; j=t;
	while(i<j){
		while(a[pos[i]]<x) i++;
		while(a[pos[j]]>x) j--;
		if(i<=j){
			k=pos[i]; pos[i]=pos[j]; pos[j]=k;
			i++; j--;
		}
	}
	if(i<t) qsort(i,t);
	if(s<j) qsort(s,j);
}

void build(long long now, long long a, long long b){
	nd[now].l=a; nd[now].r=b;
	nd[now].sum=0;
	if(a<b){
		long long mid=(a+b)>>1;
		build(now*2,a,mid);
		build(now*2+1,mid+1,b);
	}
}

long long getTree(long long now, long long a, long long b){
	if(a<=nd[now].l&&nd[now].r<=b)
		return nd[now].sum;
	long long mid=(nd[now].l+nd[now].r)>>1;
	long long lv=0,rv=0;
	if(a<=mid) lv=getTree(now*2,a,b);
	if(b>mid) rv=getTree(now*2+1,a,b);
	return lv+rv;
}

void insert(long long now, long long num){
	if(nd[now].l==nd[now].r){
		nd[now].sum++;
		return;
	}
	long long mid=(nd[now].l+nd[now].r)>>1;
	if(num<=mid) insert(now*2,num);
	else insert(now*2+1,num);
	nd[now].sum=nd[now*2].sum+nd[now*2+1].sum;
}

void init(){
	long long i,j,k;
	for(i=1;i<=n;i++){ cin>>a[i]; pos[i]=i; }
	qsort(1,n);
	rank[pos[1]]=1;
	for(i=2;i<=n;i++)
		if(a[pos[i]]==a[pos[i-1]])
			rank[pos[i]]=rank[pos[i-1]];
		else rank[pos[i]]=rank[pos[i-1]]+1;
	build(1,1,n);
}

void process(){
	long long i,j,k,ans=0;
	for(i=1;i<=n;i++){
		if(rank[i]==n) {insert(1,rank[i]); continue;}
		k=getTree(1,rank[i]+1,n);
		ans+=k;
		insert(1,rank[i]);
	}
	cout<<ans<<endl;
}

int main(){
	long long i,j,k;
	cin>>n;
	while(n!=0){
		init();
		process();
		cin>>n;
	}
	return 0;
}
