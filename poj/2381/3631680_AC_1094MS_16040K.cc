#include <iostream>
using namespace std;

bool cnt[16000001];

int main(){
	long long i,j,k, a, c, m, R0, R1, last, now, max=0;
//	freopen("2381.in","r",stdin);
	scanf("%I64d%I64d%I64d%I64d",&a,&c,&m,&R0);
	memset(cnt, 0, sizeof cnt);
	cnt[R0]=true;
	while(true){
		R1=(a*R0+c)%m;
		if(cnt[R1]) break;
		cnt[R1]=true;
		R0=R1;
	}
	last=0;
	while(!cnt[last]) last++;
	while(true){
		for(i=last+1;i<m;i++)
			if(cnt[i]) break;
		if(i==m) break;
		if(i-last>max) max=i-last;
		last=i;
		if(last==m-1) break;
	}
	printf("%I64d\n",max);
//	while(k=1);
	return 0;
}
