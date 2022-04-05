#include <iostream>
#include <algorithm>
using namespace std;

struct Ele{
	int h, a, s;
}E[401];

int N;
bool f[400010], f1[400010];

bool cmp(Ele A, Ele B){
	return (A.a<B.a);
}

void init(){
	int i,j,k;
	scanf("%d", &N);
	for(i=0; i<N; ++i)
		scanf("%d%d%d", &E[i].h, &E[i].a, &E[i].s);
	sort(E, E+N, cmp);
}

void process(){
	int i,j,k, tmp, ans=-1;
	memset(f, 0, sizeof f);
	memset(f1, 0, sizeof f1);
	
//	for(i=0; i<N; ++i) cout<<E[i].h<<' '<<E[i].a<<' '<<E[i].s<<endl;
	for(k=0; k<=E[0].s; ++k){
		if(k*E[0].h>E[0].a) continue;
		f[k*E[0].h]=f1[k*E[0].h]=1;
	}
	for(i=1; i<N; ++i){
		memset(f, 0, sizeof f);
		for(j=0; j<=E[i].a; ++j){
			if(!f1[j]) continue;
			for(k=0; k<=E[i].s; ++k){
				if(k*E[i].h+j>E[i].a) break;
				f[k*E[i].h+j]=1;
			}
		}
		for(j=0; j<=E[i].a; ++j) f1[j]=f[j];
	}
	for(i=0; i<=400001; ++i)
		if(f[i]) ans=i;
	printf("%d\n", ans);
	
}

int main(){
//	freopen("elevator.10.in", "r", stdin);
//	freopen("oo.out", "w", stdout);
	init();
	process();
//	while(1);
	return 0;
}
