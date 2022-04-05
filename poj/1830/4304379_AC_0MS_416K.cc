#include <iostream>
#include <cmath>
#define MM 50
#define eps 0.00001
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
	int i,j,k,x, r, c, rr, cc;
	bool flag = 0;
	double p, tmp;
	for(i=1; i<=N; ++i){
		p = A[i][i];  rr=cc=i;
		for(r=i; r<=N; ++r)
			for(c=i; c<=N; ++c)
				if(fabs(A[r][c])>fabs(p)){
					p=A[r][c];
					rr=r; cc=c;
				}
		if(fabs(p)<eps) break;
		
		for(j=1; j<=N; ++j){
			tmp=A[j][i]; A[j][i]=A[j][cc]; A[j][cc]=tmp;
		}
		for(j=1; j<=N; ++j){
			tmp=A[i][j]; A[i][j]=A[rr][j]; A[rr][j]=tmp;	
		}
		tmp=b[rr]; b[rr]=b[i]; b[i]=tmp;
		
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
		for(j=1; j<=N; ++j) if(fabs(A[i][j])>eps) flag = 1;
		if(!flag) break;
	}
	
	for(j=i; j<=N; ++j)
		if(fabs(b[j])>eps){
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
