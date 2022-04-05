#define maxn 10000
#define maxm 50000
#include <iostream>
using namespace std;
struct Tline{int x,y,d;};
Tline line[maxm+100];
int fa[maxm],n,m,r;
bool cmp(Tline a,Tline b){
	return (a.d>b.d);
}
int getfather(int x){
	if (fa[x]!=0) fa[x]=getfather(fa[x]); else return x;
	return fa[x];
}
int main(){
	int t;
	scanf("%d",&t);
	for (;t>0;t--){
		scanf("%d%d%d",&n,&m,&r);
		for (int i=0;i<r;i++){
			int a,b;
			scanf("%d%d%d",&line[i].x,&line[i].y,&line[i].d);
			line[i].y+=n;
		}
		sort(line,line+r,cmp);
		memset(fa,0,sizeof fa);
		int ans=(m+n)*10000;
		for (int i=0;i<r;i++){
			int fx=getfather(line[i].x);
			int fy=getfather(line[i].y);
			if (fx==fy) continue;
			fa[fx]=fy;
			ans-=line[i].d;
		};
		printf("%d\n",ans);;
	}
}
