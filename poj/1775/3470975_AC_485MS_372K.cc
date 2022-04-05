#include <iostream>
using namespace std;

int a[12],n;
bool flag;

void init(){
	int i,j,k;
	a[0]=1;
	for(i=1;i<=11;i++)
		a[i]=a[i-1]*i;
	flag=false;
}

void search(int now, int sum){
	if(now>10) return;
	if(sum>n) return;
	if(sum==n){
		flag=true;
		return;
	}
	search(now+1,sum+a[now]);
	search(now+1,sum);
}

int main(){
	int i,j,k;
	scanf("%d",&n);
	while(n>=0){
		init();
		if(n>0)
			search(0,0);
		if(flag) printf("YES\n");
		else printf("NO\n");
		scanf("%d",&n);
	}
	return 0;
}
