#include <iostream>
using namespace std;

int A[201], B[201], N;
bool vis[201];

void init(){
	int i,j,k, a, b,t;
	scanf("%d",&N);
	for(i=1;i<=N;i++){
		scanf("%d%d",&a, &b);
		if(a>b){
			t=a; a=b; b=t;
		}
	//	if(a%2==0) a--;
	//	if(b%2==0) b--;
		A[i]=a; B[i]=b;
	}
}

bool can(int i, int j){
	if(A[j]<=A[i]&&A[i]<=B[j]) return false;
	if(A[j]<=B[i]&&B[i]<=B[j]) return false;
	return true;
}

void process(){
	int i,j,k, ans=0;
	memset(vis, 0, sizeof vis);
	for(i=1;i<=N;i++)
		if(!vis[i]){
			ans+=10;
			vis[i]=1;
			for(j=1;j<=N;j++)
				if(!vis[j]&&can(j, i))
					vis[j]=1;
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
