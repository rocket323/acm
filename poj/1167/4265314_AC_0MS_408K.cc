#include <iostream>
#include <algorithm>
using namespace std;

struct road{
	int first;
	int add;
	int cnt;
}R[1000];

int A[60], res, N, Max;
int size;

int check(int a, int c){
	int i,j,k = a;
	for(k=a; k<60; k+=c){
		if(A[k]==0) return 0;
	}
	return 1;
}

int update(int now, int add){
	int i,j,k, res = 0;
	for(i=R[now].first; i<60; i+=R[now].add)
		A[i]+=add;
}

bool cmp(road A, road B){
	return A.cnt>B.cnt;
}

void init(){
	int i,j,k;
	
	memset(A, 0, sizeof A);
	
	for(i=1; i<=N; ++i){
		scanf("%d", &k);
		++A[k];
		Max = k;
	}
	size = 0;
	for(i=0; i<=29; ++i)
		for(j=i+1; j<=59-i; ++j)
			if(check(i, j)){
				size++;
				R[size].first = i;
				R[size].add = j;
				R[size].cnt = 1+(59-i)/j;
			}
	sort(R+1, R+1+size, cmp);

}

void dfs(int st, int now, int left){
	if(now>=res) return;
	
	int i;
	for(i=st; i<=size&&R[i].cnt>left; ++i);
	
	for(; i<=size; ++i){
		
		int tmp = (left-1)/R[i].cnt;
		if(now+tmp>=res) return;
		
		if(check(R[i].first, R[i].add)){
			if(left-R[i].cnt==0){
				res = now;
				return;
			}
			else{
				update(i, -1);
				dfs(i, now+1, left-R[i].cnt);				
				update(i, 1);
			}
		}
	}
	
}

void process(){
	int i,j,k;
	res = 17;
	dfs(1, 1, N);
	printf("%d\n", res);
}

int main(){
	scanf("%d", &N);
	init();
	process();
	return 0;
}
