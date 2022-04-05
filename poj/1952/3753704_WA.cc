#include <iostream>
using namespace std;

int N, A[5001], len;
int f[5001], cnt[5001], ans=0;
bool vis[65560];

int main(){
	int i,j,k;
//	freopen("1952.in","r",stdin);
	cin>>N;
	for(i=1;i<=N;i++) cin>>A[i];
	len=1;
	for(i=1;i<=N;i++) f[i]=1;
	for(i=2;i<=N;i++){
		for(j=1;j<i;j++)
			if(A[j]>A[i]&&f[j]+1>f[i])
				f[i]=f[j]+1;
		if(len<f[i]) len=f[i];
	}
	memset(cnt, 0, sizeof cnt);
	for(i=1;i<=N;i++)
		if(f[i]==1) cnt[i]=1;
	for(i=1;i<=N;i++){
		memset(vis, 0, sizeof vis);
		for(j=i+1; j<=N; j++)
			if(A[j]<A[i]&&(f[j]==f[i]+1)&&!vis[A[j]]){
				vis[A[j]]=1;
				cnt[j]+=cnt[i];
			}
	}
	for(i=1;i<=N;i++)	
		if(f[i]==len)
			ans+=cnt[i];
	cout<<len<<' '<<ans<<endl;
//	while(k=1);
	return 0;
}
