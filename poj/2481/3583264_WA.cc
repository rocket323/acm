#include <iostream>
#define Max 100005
using namespace std;

struct node{
	int l,s,e;
}nd[200001];

int n,a[200001],ans[200001];

int lowbit(int x){
	return x&(-x);
}

void add(int x){
	while(x<=Max){
		a[x]+=1;
		x+=lowbit(x);
	}
}

int getSum(int x){
	int ans=0;
	while(x>0){
		ans+=a[x];
		x-=lowbit(x);
	}
	return ans;
}

void swap(int i, int j){
	int tmp;
	tmp=nd[i].l; nd[i].l=nd[j].l; nd[j].l=tmp;
	tmp=nd[i].s; nd[i].s=nd[j].s; nd[j].s=tmp;
	tmp=nd[i].e; nd[i].e=nd[j].e; nd[j].e=tmp;
}

void qsort(int s, int t){
	int x=nd[(s+t)/2].e, y=nd[(s+t)/2].s;
	int i=s,j=t;
	while(i<j){
		while(nd[i].e>x||(nd[i].e==x&&nd[i].s>y)) i++;
		while(nd[j].e<x||(nd[j].e==x&&nd[j].s<y)) j--;
		if(i<=j){
			swap(i,j);
			i++; j--;
		}
	}
	if(s<j) qsort(s,j);
	if(i<t) qsort(i,t);
}

void init(){
	int i,j,k;
	for(i=1;i<=n;i++){
		scanf("%d%d",&nd[i].s,&nd[i].e);
		nd[i].l=i;
	}
	qsort(1,n);
//	for(i=1;i<=n;i++) cout<<nd[i].s<<' '<<nd[i].e<<endl;
}

void process(){
	int i,j,k;
	memset(a,0,sizeof a);
	for(i=1;i<=n;i++){
		k=nd[i].l;
		if(i==1||(!(nd[i].s==nd[i-1].s&&nd[i].e==nd[i-1].e))){
			ans[k]=getSum(nd[i].s+1);
			add(nd[i].s+1);
		//	if(i==1) cout<<nd[i].s<<endl;
		}
		else{
			ans[k]=ans[nd[i-1].l];
			add(nd[i].s+1);
		}
	}
	for(i=1;i<n;i++) printf("%d ",ans[i]);
	printf("%d\n",ans[n]);
}

int main(){
	int i,j,k;
//	freopen("2481.in","r",stdin);
	scanf("%d",&n);
	while(n!=0){
		init();
		process();
		
		scanf("%d%d",&n);
	}
//	while(k=1);
	return 0;
}
