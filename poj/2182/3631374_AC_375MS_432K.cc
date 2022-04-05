#include <iostream>
using namespace std;

int N, A[8001], ans[8001];

void process(){
	int i,j,k, rec;
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++)
			if(A[j]==0)
				rec=j;
		ans[rec]=i;
		for(j=rec;j<=N;j++) A[j]--;
	}
	for(i=1;i<=N;i++) printf("%d\n",ans[i]);
}

int main(){
	int i,j,k;
//	freopen("2182.in","r",stdin);
	scanf("%d",&N);
	for(i=2;i<=N;i++) scanf("%d",&A[i]);
	A[1]=0;
	process();
//	while(k=1);
	return 0;
}
