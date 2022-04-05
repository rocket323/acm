#include <iostream>
#define MaxN 50001
using namespace std;

int N, P, pre[MaxN],to[MaxN], from[MaxN], ans;

void init(){
	int i,j,k;
	scanf("%d%d",&N, &P);
	for(i=1;i<=N;i++) pre[i]=i;
	memset(to, 0, sizeof to);
	memset(from, 0, sizeof from);
}

bool check(int q, int a, int b){
	if(a>N||b>N) return false;
	if(q==2&&a==b) return false;
	return true;
}

int find(int now){
	if(pre[now]==now) return now;
	int ans=find(pre[now]);
	pre[now]=ans;
	return ans;
}

void process(){
	int i,j,k, q, a, b, ta,tb, fa, fb, x, y;
	ans=0;
	for(i=1;i<=P;i++){
		scanf("%d%d%d",&q, &a, &b);
		if(!check(q, a, b)){
			ans++;
			continue;
		}
		x=find(a); y=find(b);
		ta=find(to[x]); fa=find(from[x]);
		tb=find(to[y]); fb=find(from[y]);
		
		if(q==1){
			if(to[x]==y||from[x]==y||ta!=tb||fa!=fb){
				ans++;
				continue;
			}
			pre[y]=x;
		}
		else if(q==2){
			if(ta!=fb){
				ans++;
				continue;
			}
			to[x]=y;
			from[y]=x;
		}
	}
	printf("%d\n",ans);
}

int main(){
	int i,j,k;
//	freopen("1182.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
