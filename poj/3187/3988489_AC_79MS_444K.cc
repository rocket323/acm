#include <iostream>
using namespace std;

int N, sum, A[11], C[11][11];
bool flag, vis[11];

void getC(){
	int i,j,k;
	memset(C, 0, sizeof C);
	for(i=0; i<=10; i++) C[i][0]=1;
	for(i=1; i<=10; i++)
		for(j=1; j<=i; j++)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
}

bool check(){
	int i, ans=0;
	for(i=1; i<=N; ++i) ans+=(A[i]*C[N-1][i-1]);
	if(ans==sum) return true;
	else return false;
}

void dfs(int now){
	if(flag) return;
	if(now==N+1){
		if(check()){
			flag=1;
			for(int i=1; i<N; ++i) cout<<A[i]<<' ';
			cout<<A[N]<<endl;
		}
		return;
	}
	for(int i=1; i<=N; ++i){
		if(!vis[i]){
			vis[i]=1;
			A[now]=i;
			dfs(now+1);
			vis[i]=0;
		}
	}
}

int main(){
	int i,j,k;
//	freopen("3187.in", "r", stdin);
	cin>>N>>sum;
	flag=0;
	getC();
	dfs(1);
//	while(1);
	return 0;
}
