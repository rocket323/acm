#include <iostream>
#define MaxN 50001
using namespace std;
//并查集。。最重要的思想 ： 节点与根的关系。。。 
int N, P, pre[MaxN], d[MaxN], ans;

void init(){
	int i,j,k;
	scanf("%d%d",&N, &P);
	for(i=0;i<=N;i++) pre[i]=i;
	memset(d, 0, sizeof d);
}

bool check(int q, int a, int b){
	if(a>N||b>N) return false;
	if(q==2&&a==b) return false;
	return true;
}

int find(int now){
	if(pre[now]==now) return now;
	int ans=find(pre[now]);
	int k=pre[now];

	if(d[now]==0&&d[k]==0) d[now]=0;
	else if(d[now]==0&&d[k]==1) d[now]=1;
	else if(d[now]==0&&d[k]==2) d[now]=2;
	else if(d[now]==1&&d[k]==0) d[now]=1;
	else if(d[now]==1&&d[k]==1) d[now]=2;
	else if(d[now]==1&&d[k]==2) d[now]=0;
	else if(d[now]==2&&d[k]==0) d[now]=2;
	else if(d[now]==2&&d[k]==1) d[now]=0;
	else if(d[now]==2&&d[k]==2) d[now]=1;
	pre[now]=ans;
	return ans;
}

int fun(int a, int b){
	int ans,i,j;
	if(d[a]==0&&d[b]==0) return 1;
	if(d[a]==0&&d[b]==1) return -2;
	if(d[a]==0&&d[b]==2) return 2;
	if(d[a]==1&&d[b]==0) return 2;
	if(d[a]==1&&d[b]==1) return 1;
	if(d[a]==1&&d[b]==2) return -2;
	if(d[a]==2&&d[b]==0) return -2;
	if(d[a]==2&&d[b]==1) return 2;
	if(d[a]==2&&d[b]==2) return 1;
//	if(d[a]==-1){
//		if(d[b]==0) return 1;
//		if(d[b]==1) return 
	cout<<d[a]<<' '<<d[b]<<endl;
}

void process(){
	int i,j,k, q, a, b, x, y;
	ans=0;
	for(i=1;i<=P;i++){
		scanf("%d%d%d",&q, &a, &b);
		if(!check(q, a, b)){
			ans++;
			continue;
		}
		x=find(a); y=find(b);
		if(x!=y){
			if(q==1){
				pre[y]=a;
				//if(d[b]==-1) d[y]=0;
				if(d[b]==0) d[y]=0;
				else if(d[b]==1) d[y]=2;
				else if(d[b]==2) d[y]=1;
			}
			else {
				pre[y]=a;
				//if(d[b]==-1) d[y]=2;
				if(d[b]==0) d[y]=2;
				else if(d[b]==1) d[y]=1;
				else if(d[b]==2) d[y]=0;
			}
		}
		else{
			if(fun(a, b)!=q)
				ans++;
		}
	}
	printf("%d\n",ans);
}

int main(){
	int i,j,k;
//	freopen("eat8.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
