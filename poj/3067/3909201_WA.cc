#include <iostream>
#define MaxN 10001
#include <algorithm>
using namespace std;

struct node{
	int a, b;
}Q[2000000];

int N, M, P, C[MaxN];

bool cmp(node A, node B){
	return A.a>B.a;
}

int lowbit(int x){
	return x&(-x);
}

void add(int x){
	while(x<MaxN){
		C[x]+=1;
		x+=lowbit(x);
	}
}

int getSum(int x){
	int ans=0;
	while(x>0){
		ans+=C[x];
		x-=lowbit(x);
	}
	return ans;
}

void init(){
	int i,j,k;
	scanf("%d%d%d", &N, &M, &P);
	for(i=0; i<P; ++i)
		scanf("%d%d", &Q[i].a, &Q[i].b);
}

void process(int tes){
	int i,j,k, ans=0, end;
	sort(Q, Q+P, cmp);
	
	memset(C, 0, sizeof C);
	
	for(i=0; i<P; ++i){
		ans+=getSum(Q[i].b);
		for(j=i+1; j<P&&Q[j].a==Q[i].a; ++j){
			ans+=getSum(Q[j].b);
		}
		
		if(Q[j].a==Q[i].a) end=j;
		else end=j-1;

		for(k=i; k<=end; ++k){
			add(Q[k].b+1);
		}
		i=j-1;
	}

	printf("Test case %d: %d\n", tes, ans);
}

int main(){
	int i,j,k, T;
//	freopen("3067.in", "r", stdin);
	scanf("%d", &T);
	for(i=1; i<=T; ++i){
		init();
		process(i);
	}
//	while(k=1);
	return 0;
}
