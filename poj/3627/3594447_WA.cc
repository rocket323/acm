#include <iostream>
using namespace std;

int N,B, s[20001],A[20001],cnt[10001];

int main(){
	int i,j,k,tp=0;
//	freopen("3627.in","r",stdin);
	scanf("%d%d",&N,&B);
	memset(s,0,sizeof s);
	memset(cnt,0,sizeof cnt);
	for(i=1;i<=N;i++){
		scanf("%d",&k);
		cnt[k]++;
	}
	for(i=1000;i>=0;i--)
		for(j=1;j<=cnt[i];j++){
			tp++;
			A[tp]=i;
		}
	for(i=1;i<=N;i++){
		s[i]=s[i-1]+A[i];
		if(s[i]>=B){
			printf("%d\n",i);
			break;
		}
	}
//	while(k=1);
	return 0;
}
