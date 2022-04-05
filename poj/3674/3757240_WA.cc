#include <iostream>
using namespace std;

int f[301][7],N;
int D[301], E[301], ans;
int sum[301];
bool vis[301];

void init(){
	int i,j,k,t;
	ans=0; sum[0]=0;
	for(i=1;i<=N;i++){
		cin>>D[i]>>E[i];
		D[i]/=10;
		sum[i]=sum[i-1]+D[i]*20;
	}
	for(i=1;i<N;i++)
		for(j=i+1;j<=N;j++)
			if(D[i]<D[j]){
				t=D[i]; D[i]=D[j]; D[j]=t;
				t=E[i]; E[i]=E[j]; E[j]=t;
			}
}

void dfs(int now, int last, int dam){
	if(dam+sum[6-now]<=ans) return;
	if(now==6){
		if(dam>ans)
			ans=dam;
		return;
	}
	int i;
	for(i=1;i<=N;i++){
		if(vis[i]) continue;
		vis[i]=1;
		dfs(now+1, i, dam+D[i]*(10+E[last]));
		vis[i]=0;
	}
}

int main(){
	int i,j,k, t;
//	freopen("3674.in","r",stdin);
	while(cin>>N){
		init();
		E[0]=0;
		dfs(0, 0, 0);
		cout<<ans<<endl;
	}
//	while(k=1);
	return 0;
}
