#include <iostream>
#define MaxN 10001
#define MaxL 1000000010
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
	}
	sort(p+1, p+N+1, cmp);
	
//	for(i=1; i<=N; i++)
//		cout<<p[i].num<<' '<<p[i].idx<<endl;
	
	Low=p[1].num;	
}

int Min(int a, int b){
	return (a<b)?a:b;
}

void process(){
	int i,j,k, ans=0, cnt;
	memset(lt, -1, sizeof lt);
	for(i=1; i<=N; ++i){
		if(lt[i]!=-1) continue;
		k=i; sum=0; L=p[k].num; cnt=0;
		
		while(lt[k]==-1){
			cnt++;
			lt[k]=1;
			sum+=p[k].num;
			k=p[k].idx;
		}
		ans+=Min((cnt-2)*L+sum, L+(1+cnt)*Low+sum);
	}
	printf("%d\n", ans);
}

int main(){
	int i,j,k;
//	freopen("csort.9.in", "r", stdin);
//	freopen("ss.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	init();
	process();
//	while(1);
	return 0;
}
