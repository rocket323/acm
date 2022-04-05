#include <iostream>
using namespace std;

int N, A[5001], len;
int f[5001], cnt[5001], ans=0;
bool vis[65560];

int main(){
	int i,j,k;
//	freopen("buylow.6.in","r",stdin);
//	freopen("out.out","w",stdout);
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
	for(i=2;i<=N;i++){
		memset(vis, 0, sizeof vis);
		for(j=i-1;j>=1;j--)
			if(A[j]>A[i]&&(f[j]==f[i]-1)&&!vis[A[j]]){
				vis[A[j]]=1;
				cnt[i]+=cnt[j];
			}
	}
	memset(vis, 0, sizeof vis);
	for(i=N;i>=1;i--)
		if(!vis[A[i]]&&f[i]==len){
			ans+=cnt[i];
			vis[A[i]]=1;
		}
	cout<<len<<' '<<ans<<endl;
//	while(k=1);
	return 0;
}
