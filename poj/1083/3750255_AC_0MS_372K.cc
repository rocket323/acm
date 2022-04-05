#include <iostream>
using namespace std;

int A[201], B[201], N;
int cnt[500];
bool vis[201];

void init(){
	int i,j,k, a, b,t;
	scanf("%d",&N);
	for(i=1;i<=N;i++){
		scanf("%d%d",&a, &b);
		if(a>b){
			t=a; a=b; b=t;
		}
		if(a%2==0) a--;
		if(b%2==0) b--;
		A[i]=a; B[i]=b;
	}
}

void process(){
	int i,j,k, ans=0;
	memset(vis, 0, sizeof vis);
	memset(cnt, 0, sizeof cnt);
	for(i=1;i<=N;i++){
		for(j=A[i];j<=B[i];j++){
			cnt[j]+=10;
			if(cnt[j]>ans) ans=cnt[j];
		}
	}
	printf("%d\n",ans);
}

int main(){
	int i,j,k,T;
//	freopen("1083.in","r",stdin);
	scanf("%d",&T);
	for(i=1;i<=T;i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
