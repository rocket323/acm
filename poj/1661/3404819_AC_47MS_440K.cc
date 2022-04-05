#include <iostream>
#define MaxL 100000000
using namespace std;

int x1[1001],x2[1001],h[1001],n,x,y,M,s;
int f[1001][3];
bool vis[1001][3];

void init(){
	int i,j,k;
	scanf("%d%d%d%d",&n,&x,&y,&M);
	for(i=1;i<=n;i++)
		scanf("%d%d%d",&x1[i],&x2[i],&h[i]);
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
			if(h[i]<h[j]){
				k=h[i]; h[i]=h[j]; h[j]=k;
				k=x1[i]; x1[i]=x1[j]; x1[j]=k;
				k=x2[i]; x2[i]=x2[j]; x2[j]=k;
			}
}

int Min(int a, int b){
	return (a<b)?a:b;
}

bool cross(int a, int b, int c){
	if(b<=a&&a<=c) return true;
	return false;
}

bool check(int x, int t){
	int i;
	for(i=t+1;i<=n;i++)
		if(x1[i]<x&&x<x2[i])
			return false;
	return true;
}

void process(){
	int i,j,k,ans=MaxL;
	s=1;
	while(h[s]>y||!(x1[s]<=x&&x2[s]>=x)){
		s++;
		if(s>n) break;
	}
	memset(vis,0,sizeof vis);
	f[s][1]=(y-h[s])+(x-x1[s]);
	f[s][2]=(y-h[s])+(x2[s]-x);
	for(i=s+1;i<=n;i++){
		f[i][1]=MaxL; f[i][2]=MaxL;
		for(j=s;j<i;j++){
			if(cross(x1[j],x1[i],x2[i])&&(h[j]-h[i]<=M)&&!vis[j][1]){
				if(x1[i]<x1[j]&&x1[j]<x2[i]) vis[j][1]=true;
				f[i][2]=Min(f[i][2],f[j][1]+(x2[i]-x1[j])+(h[j]-h[i]));
				f[i][1]=Min(f[i][1],f[j][1]+(x1[j]-x1[i])+(h[j]-h[i]));
			}
			if(cross(x2[j],x1[i],x2[i])&&(h[j]-h[i]<=M)&&!vis[j][2]){
				if(x1[i]<x2[j]&&x2[j]<x2[i]) vis[j][2]=true;
				f[i][2]=Min(f[i][2],f[j][2]+(x2[i]-x2[j])+(h[j]-h[i]));
				f[i][1]=Min(f[i][1],f[j][2]+(x2[j]-x1[i])+(h[j]-h[i]));
			}
		}
	}
	for(i=s;i<=n;i++){
		if(h[i]<=M){
			if(check(x1[i],i)){
				//cout<<i<<' '<<1<<endl;
				ans=Min(ans,f[i][1]+h[i]);
			}
			if(check(x2[i],i)){
				//cout<<i<<' '<<2<<endl;
				ans=Min(ans,f[i][2]+h[i]);
			}
		}
	}
	if(ans==MaxL){
		cout<<y<<endl;
		return;
	}
	cout<<ans<<endl;
}

int main(){
	int i,j,k,t;
	scanf("%d",&t);
	for(i=1;i<=t;i++){
		init();
		process();
	}
	return 0;
}
