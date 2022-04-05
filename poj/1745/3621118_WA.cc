#include <iostream>
using namespace std;

bool f[101], f1[101];
int N,P, A[10001];

int main(){
	int i,j,k,tmp;
//	freopen("1745.in","r",stdin);
	scanf("%d%d",&N,&P);
	for(i=1;i<=N;i++)
		scanf("%d",&A[i]);
	memset(f1,0,sizeof f1);
	f1[A[1]%P]=true; f[A[1]%P]=true;
	for(i=2;i<=N;i++){
		memset(f,0,sizeof f);
		for(j=0;j<P;j++)
			if(f1[j]){
				tmp=(j+A[i])%P;
				f[tmp]=true;
				tmp=(j-A[i])%P;
				f[tmp]=true;
			}
		memcpy(f1, f, sizeof f);
	}
	if(f[0]) printf("Divisible\n");
	else printf("Not divisible\n");
//	while(k=1);
	return 0;
}
	
