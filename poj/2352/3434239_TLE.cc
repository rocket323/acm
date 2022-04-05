#include <iostream>
#define Max 32000
using namespace std;

int maxn=0,n,a[32001]={0},l[15001],level[15001]={0};

int lowbit(int x){
	return x&(-x);
}

void update(int x){
	while(x<=Max){
		a[x]+=1;
		x+=lowbit(x);
	}
}

int getsum(int x){
	int ans=0;
	while(x>0){
		ans+=a[x];
		x-=lowbit(x);
	}
	return ans;
}

int main(){
	int i,j,k,x,y;
	scanf("%d",&n);
	memset(level,0,sizeof level);
	for(i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		l[i]=getsum(x);
		level[l[i]]++;
		update(x);
	}
	for(i=0;i<n;i++) printf("%d\n",level[i]);
	return 0;
}
