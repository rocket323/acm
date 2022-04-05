#include <iostream>
#define Max 32001
using namespace std;

int n,a[32002]={0},l[15001],level[15001]={0};

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
		l[i]=getsum(x+1);
		level[l[i]]++;
		update(x+1);
	}
	for(i=0;i<n;i++) printf("%d\n",level[i]);
	return 0;
}
