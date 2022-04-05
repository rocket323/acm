#include <iostream>
#define MaxN 10001
#define MaxL 100000001
using namespace std;

struct pairp{
	int num, idx;
}p[MaxN];

int N, Low, L, sum, lt[MaxN];

bool cmp(pairp A, pairp B){
	return (A.num<B.num);
}

void init(){
	int i,j,k;
	Low=MaxL;
	scanf("%d", &N);
	for(i=1; i<=N; i++){
		scanf("%d", &k);
		p[i].num=k;
		p[i].idx=i;
		if(k<Low) Low=k;
	}
	sort(p+1, p+N+1, cmp);
}

int Min(int a, int b){
	return (a<b)?a:b;
}

void process(){
	int i,j,k, ans=0, cnt;
	memset(lt, -1, sizeof lt);
	for(i=1; i<=N; ++i){
		if(lt[i]!=-1) continue;
		k=i; sum=0; L=MaxL; cnt=0;
		while(lt[k]==-1){
			cnt++;
			lt[k]=1; L=Min(L, p[k].num);
			sum+=p[k].num;
			k=p[k].idx;
		}
		ans+=Min((cnt-2)*L+sum, 2*L+cnt*Low+sum);
	}
	printf("%d\n", ans);
}

int main(){
	int i,j,k;
//	freopen("3270.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
