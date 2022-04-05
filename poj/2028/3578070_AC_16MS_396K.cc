#include <iostream>
using namespace std;

int n,q,m;
int cnt[101];

void init(){
	int i,j,k,maxL=0,rec=0;
	memset(cnt,0,sizeof cnt);
	for(i=1;i<=n;i++){
		scanf("%d",&m);
		for(j=1;j<=m;j++){
			scanf("%d",&k);
			cnt[k]++;
		}
	}
	for(i=0;i<=100;i++)
		if(cnt[i]>maxL){
			rec=i;
			maxL=cnt[i];
		}
	if(maxL>=q)
		printf("%d\n",rec);
	else printf("0\n");
}

int main(){
	int i,j,k;
//	freopen("2028.in","r",stdin);
	scanf("%d%d",&n,&q);
	while(n!=0){
		init();
		scanf("%d%d",&n,&q);
	}
//	while(k=1);
	return 0;
}
