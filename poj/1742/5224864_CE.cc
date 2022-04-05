#include <iostream>
using namespace std;

bool f[100001];
int n,m,a[101],c[101],cnt[100001],l[100001];
int aa[101],cc[101],tp;

void init(){
	int i,j,k,tmp;
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(i=1;i<=n;i++)
		scanf("%d",&c[i]);
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
			if(a[i]>a[j]){
				tmp=a[i]; a[i]=a[j]; a[j]=tmp;
				tmp=c[i]; c[i]=c[j]; c[j]=tmp;
			}
	tp=1; aa[1]=a[1]; cc[1]=c[1];
	for(i=2;i<=n;i++){
		if(a[i]==a[i-1])
			cc[tp]+=c[i];
		else{
			tp++;
			aa[tp]=a[i];
			cc[tp]=c[i];
		}
	}
	memset(f,0,sizeof f);
	memset(cnt,0,sizeof cnt);
	memset(l,0,sizeof l);
}

void process(){
	int i,j,k,t=0,tmp;
	f[0]=true;
	for(i=1;i<=tp;i++){
		t+=aa[i]*cc[i]; if(t>m) t=m;
		for(j=aa[i];j<=t;j++){
			tmp=j-a[i];
			if(f[tmp]&&(!f[j])){
				if(l[tmp]==i&&cnt[tmp]<cc[i]){
					f[j]=true;
					cnt[j]=cnt[tmp]+1;
					l[j]=l[tmp];
					continue;
				}
				if(l[tmp]!=i&&cc[i]>0){
					f[j]=true;
					cnt[j]=1;
					l[j]=i;
					continue;
				}
			}
		}
	}
	int ans=0;
	for(i=1;i<=m;i++) if(f[i]) ans++;
	printf("%d\n",ans);
}

int main(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	while(n!=0){	
		init();
		process();
		scanf("%d%d",&n,&m);
	}
	return 0;
}
