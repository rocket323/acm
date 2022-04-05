#include <iostream>
using namespace std;

int n,f[1001],a[1001];

void process(){
	int i,j,k;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	f[1]=1;
	for(i=2;i<=n;i++){
		f[i]=1;
		for(j=1;j<i;j++)
			if(a[j]<a[i]&&f[j]+1>f[i])
				f[i]=f[j]+1;
	}
	int ans=0;
	for(i=1;i<=n;i++)
		if(f[i]>ans) ans=f[i];
	printf("%d\n",ans);
}

int main(){
	int i,j,k;
	while(cin>>n)
		process();
	return 0;
}
