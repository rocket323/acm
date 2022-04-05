#include <iostream>
using namespace std;

int a[12],n;
bool flag;

void init(){
	int i,j,k;
	a[1]=1;
	for(i=2;i<=11;i++)
		a[i]=a[i-1]*i;
	flag=false;
}

void search(int now, int sum){
	if(now>9) return;
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
	while(n!=-1){
		init();
		search(1,0);
		if(flag) printf("YES");
		else printf("NO");
		scanf("%d",&n);
	}
	return 0;
}
