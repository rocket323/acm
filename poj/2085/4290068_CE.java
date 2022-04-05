#include <iostream>
#define MM 50010
using namespace std;

int A[MM], C[MM], P[MM];
int vis[MM], N, M;

int lowbit(int x){ return x&(-x); }

void add(int x, int num){
	while(x<MM){
		C[x] += num;
		x += lowbit(x);
	}
}

int getSum(int x){
	int res = 0;
	while(x){
		res += C[x];
		x -= lowbit(x);
	}
	return res;
}

int check(int x, int cnt){
	int res = x-1;
	res += (cnt-1)*cnt/2;	
	return res;
}

void process(){
	int i,j,k, l, r, mid, rank, x;
	memset(vis, 0, sizeof vis);
	
	for(i=1; i<=N; ++i) add(i, 1);

	
	for(i=1; i<=N; ++i){
		l=1; r=N-i+1;
		while(l<=r){
			mid=(l+r)>>1;
			k=check(mid, N-i);
			if(k>=M){
				rank = mid;
				r = mid-1;
			}
			else l = mid+1;	
		}
		/*
		for(j=1; j<=N; ++j)
			if(!vis[j]&&check(j, N-i)>=M){
				res = j;
				break;
			}*/
			
		l=1; r=N;
		while(l<=r){
			mid = (l+r)>>1;
			k = getSum(mid);
			if(k>=rank){
				x = mid;
				r = mid-1;
			}
			else l = mid+1;
		}
			
		A[i] = x;
		M -= (rank-1);
		add(x, -1);
	}
	for(i=1; i<N; ++i) printf("%d ", A[i]);
	printf("%d\n", A[N]);	
}

int main(){
//	freopen("2085.in", "r", stdin);
	scanf("%d%d", &N, &M);
	while(N!=-1){
		process();
		scanf("%d%d", &N, &M);
	}
//	while(1);
	return 0;
}
