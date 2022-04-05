#include <iostream>
#include <cmath>
#define MM 30
#define eps 0.000001
using namespace std;

int N, S1[MM], S2[MM];
double b[MM];
double A[MM][MM];

void init(){
	int i,j,k, aa, bb;

	scanf("%d", &N);
	for(i=1; i<=N; ++i) scanf("%d", &S1[i]);
	for(i=1; i<=N; ++i) scanf("%d", &S2[i]);

	for(i=1; i<=N; ++i)
		if(S1[i]==S2[i]) b[i] = 0;
		else b[i] = 1;
		
	for(i=1; i<=N; ++i)
		for(j=1; j<=N; ++j)
			if(i==j) A[i][j] = 1;
			else A[i][j] = 0;
			
	scanf("%d%d", &aa, &bb);
	while(aa!=0){
		A[bb][aa] = 1;
		scanf("%d%d", &aa, &bb);
	}
}

void process(){
	int i,j,k,x;
	bool flag = 0;
	double p, tmp;
	for(i=1; i<=N; ++i){
		x = i;
		for(j=i+1; j<=N; ++j)
			if(fabs(A[j][i])>fabs(A[x][i])+eps) x = j;
		for(j=1; j<=N; ++j){
			tmp=A[x][j]; A[x][j]=A[i][j]; A[i][j]=tmp;
		}
		tmp=b[i]; b[i]=b[x]; b[x]=tmp;
		
		if(fabs(A[x][i])<eps) continue;
		
		for(j=i+1; j<=N; ++j){
			tmp=A[j][i]/A[i][i];
			for(k=i; k<=N; ++k)
				A[j][k] -= A[i][k]*tmp;
			b[j] -= b[i]*tmp;
		}
	}
/*	
	for(i=1; i<=N; ++i){
		for(j=1; j<=N; ++j)
			printf("%.f ", A[i][j]);
		cout<<b[i]<<endl;
	}*/
	
	for(i=1; i<=N; ++i){
		flag = 0;
		if(fabs(A[i][i])>eps) flag = 1;
		if(!flag) break;
	}
	for(j=i; j<=N; ++j)
		if(fabs(b[j]-1)<eps){
			printf("Oh,it's impossible~!!\n");
			return;
		}
	int tt = 1<<(N+1-i);
	printf("%d\n", tt);
}

int main(){
	int T;
//	freopen("1830.in", "r", stdin);
	scanf("%d", &T);
	for(int i=1; i<=T; ++i){
		init();
		process();
	}
//	while(1);
	return 0;
}
