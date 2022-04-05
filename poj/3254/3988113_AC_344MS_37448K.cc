#include <iostream>
#define Mod 100000000
using namespace std;

int N, M;
int G[13][13];
int S[13][5000], num[13][5000], cnt[13];
//next
int f[12][5000][145], f1[5000][145], Sum;
bool vis[13], v1[13], v2[13];

void preset(int row){
	int x, i,j,k, s, tmp, cc;
	bool flag;
	for(x=0; x<(1<<M); ++x){
		memset(vis, 0, sizeof vis);
		for(i=1; i<=M; ++i){
			tmp=1<<(i-1);
			if(x&tmp) vis[i]=1;
		}
		flag=1;
		for(i=2; i<=M; ++i)
			if(vis[i]&&vis[i-1]){
				flag=0;
				break;
			}
			
		cc=0;
		for(i=1; i<=M; ++i)
			if(vis[i]){
				if(G[row][i]==0){
					flag=0;
					break;
				}
				else cc++;
				
			}
		if(flag){
			cnt[row]++;
			S[row][cnt[row]]=x;
			num[row][cnt[row]]=cc;
		//	cout<<row<<" : "<<x<<' '<<cc<<endl;
		}
	}
	
}

void init(){
	int i,j,k;
	cin>>N>>M;
	Sum=0;
	for(i=1; i<=N; ++i)
		for(j=1; j<=M; ++j){
			cin>>G[i][j];
			if(G[i][j]==1) Sum++;
		}
	memset(cnt, 0, sizeof cnt);
	for(i=1; i<=N; i++){
		preset(i);
	}
}

bool can(int s1, int s2){
	int i,j,k, tmp;
	memset(v1, 0, sizeof v1);
	memset(v2, 0, sizeof v2);
	for(i=1; i<=M; ++i){
		tmp=1<<(i-1);
		if(s1&tmp) v1[i]=1;
		if(s2&tmp) v2[i]=1;
		if(v1[i]&&v2[i]) return false;
	}
	return true;
}

void process(){
	int i,j,k, tot, s1, s2, jj;
	int ans=0;
	
//	for(i=1; i<=N; ++i) cout<<cnt[i]<<endl;
/*	for(i=1; i<=N; ++i){
		for(j=1; j<=cnt[i]; ++j)
			cout<<S[i][j]<<' ';
		cout<<endl;
	}*/
	
	memset(f, 0, sizeof f);
	memset(f1, 0, sizeof f1);
	for(i=1; i<=cnt[1]; ++i){
		k=S[1][i]; tot=num[1][i];
	//	f[i][tot]=f1[i][tot]=1;
		f[1][i][tot]=1;
	}		
	
	
	for(i=2; i<=N; ++i){
		for(j=1; j<=cnt[i]; ++j){
			s1=S[i][j];
			for(k=0; k<=Sum; ++k){
				if(k-num[i][j]<0) continue;
				for(jj=1; jj<=cnt[i-1]; ++jj){
					s2=S[i-1][jj];
				//	if(j==2) cout<<s1<<' '<<s2<<' '<<can(s1, s2)<<endl;
					if(can(s1, s2)){
						f[i][j][k]=(f[i][j][k]+f[i-1][jj][k-num[i][j]])%Mod;
						
					}
				}
			}
		}
	
	}
	for(j=1; j<=cnt[N]; ++j)
		for(k=num[N][j]; k<=Sum; ++k){
			ans=(ans+f[N][j][k])%Mod;
		//	cout<<j<<' '<<k<<" : "<<f[j][k]<<endl;
		}
	
	printf("%d\n", ans);

}

int main(){
	int i,j,k;
//	freopen("cowfood.11.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	init();
	process();
//	while(1);
	return 0;
}
