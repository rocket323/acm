#include <iostream>
#include <algorithm>
using namespace std;

int N, S[101], A[101], M;
int vis[101];

void init(){
	int i,j,k;
	M = (N-1)*N/2;
	for(i=1; i<=M; ++i) scanf("%d", &S[i]);
	sort(S+1, S+1+M);
}

int check(){
	int flag;
	int i,j,k;
	for(i=4; i<=N; ++i){
		for(j=1; j<=M; ++j)
			if(!vis[j]){
				vis[j] = 1;
				A[i] = S[j]-A[1];
				break;
			}
		for(j=1; j<i; ++j){
			int tmp = A[j]+A[i];
			flag = 0;
			for(k=1; k<=M; ++k)
				if(S[k]==tmp&&!vis[k]){
					vis[k] = 1;
					flag = 1;
					break;
				}
		//	if(!flag) return 0;
		}
	}
	return 1;
}

void process(){
	int i,j,k, x;
	k = S[2]-S[1];
	for(i=3; i<=M; ++i){
		x = S[i]+k;
		if(x&1) continue;
		memset(vis, 0, sizeof vis);
		vis[1]=vis[2]=vis[3]=1;
		A[3] = x/2;
		A[2] = S[i]-A[3];
		A[1] = S[1]-A[2];
		if(check()){
			for(j=1; j<N; ++j) printf("%d ", A[j]);
			printf("%d\n", A[N]);
			return;
		}
	}
	printf("Impossible\n");
}

int main(){
//	freopen("2466.in", "r", stdin);
	while(scanf("%d", &N)!=EOF){
		init();
		process();
	}
//	while(1);
	return 0;
}
