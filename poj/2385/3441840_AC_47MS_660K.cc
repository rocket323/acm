#include <iostream>
using namespace std;

int f1[1001][31],f2[1001][31],a[1001];
bool c1[1001][31]={0},c2[1001][31]={0};

int Max(int a, int b){
	return (a>b)? a : b;
}  

int main(){
	int i,j,k,n,w,t,p,ans=0;
	int p1,p2;
	
	scanf("%d%d",&n,&w);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);

	memset(f1,0,sizeof f1); memset(f2,0,sizeof f2);
	f1[1][0]=(a[1]==1)?1:0; c1[1][0]=1;
	f2[1][0]=(a[2]==2)?1:0; c2[1][0]=1;
	for(i=2;i<=n;i++){
		t=i-1; if(t>w) t=w;
		for(j=0;j<=t;j++){
			if(j==0){
				if(c2[i-1][j]){
					c2[i][j]=true;
					p=(a[i]==2)?1:0;
					f2[i][j]=f2[i-1][j]+p;
				}
				if(c1[i-1][j]){
					c1[i][j]=true;
					p=(a[i]==1)?1:0;
					f1[i][j]=f1[i-1][j]+p;
				}
			}
			else{
				if(c1[i-1][j-1]||c2[i-1][j]){
					c2[i][j]=true;
					p1=(a[i]==2)?1:0; p2=(a[i]==2)?1:0;
					f2[i][j]=Max((f1[i-1][j-1]+p1)*c1[i-1][j-1],(f2[i-1][j]+p2)*c2[i-1][j]); 
				}
				if(c1[i-1][j]||c2[i-1][j-1]){
					c1[i][j]=true;
					p1=(a[i]==1)?1:0; p2=(a[i]==1)?1:0;
					f1[i][j]=Max((f1[i-1][j]+p1)*c1[i-1][j], (f2[i-1][j-1]+p2)*c2[i-1][j-1]);
				}
			}
		}
	}
	for(i=1;i<=n;i++)
		for(j=0;j<=w;j++){
			if(f1[i][j]>ans) ans=f1[i][j];
			if(f2[i][j]>ans) ans=f2[i][j];
		}
	printf("%d\n",ans);
	return 0;
}
