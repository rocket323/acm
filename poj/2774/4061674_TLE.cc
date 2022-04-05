#include <iostream>
#include <algorithm>
#define MaxN 100010
using namespace std;

char S1[MaxN], S2[MaxN], S[2*MaxN];
int list[MaxN], rank[MaxN], tmp[MaxN], A[2][MaxN], C[MaxN];
int Height[MaxN], l1, l2;
int N, ans;

void init(){
	int i,j,k;
	strcpy(S, "");
	strcpy(S, S1); strcat(S, "$");
	strcat(S, S2);
	l1=strlen(S1); l2=strlen(S2);
	N=strlen(S);
}

bool cmp(int i, int j){
	return S[i]<S[j];
}

void bsort(int key){
	int i, k;
	memset(C, 0, sizeof C);
	for(i=0; i<N; ++i) tmp[i]=list[i];
	for(i=0; i<N; ++i) C[A[key][i]]++;
	for(i=1; i<N; ++i) C[i]+=C[i-1];
	for(i=N-1; i>=0; --i){
		k=A[key][tmp[i]];
		list[C[k]-1]=tmp[i];
		C[k]--;
	}
}

void Suffix_Sort(){
	int i,j,k, h;
	for(i=0; i<N; ++i) list[i]=i;
	sort(list, list+N, cmp);
	rank[list[0]]=0;
	for(i=1; i<N; ++i)
		if(S[list[i]]==S[list[i-1]]) rank[list[i]]=rank[list[i-1]];
		else rank[list[i]]=rank[list[i-1]]+1;
	
	for(h=1; h<N; h<<=1){
		for(i=0; i<N; ++i){
			A[0][i]=rank[i];
			if(i+h<N) A[1][i]=rank[i+h];
			else A[1][i]=0;
		}
		bsort(1);
		bsort(0);
		rank[list[0]]=0;
		for(i=1; i<N; ++i){
			if(A[0][list[i]]==A[0][list[i-1]]&&A[1][list[i]]==A[1][list[i-1]])
				rank[list[i]]=rank[list[i-1]];
			else rank[list[i]]=rank[list[i-1]]+1;
		}
	}
}

void getHeight(){
	int i,j,k, h;
	Height[0]=0;
	for(i=0; i<N; ++i) rank[list[i]]=i;
	for(h=0, i=0; i<N; ++i){
		if(rank[i]>0){
			j=list[rank[i]-1];
			while(S[j+h]==S[i+h]) ++h;
			Height[rank[i]]=h;
			if(h>0) --h;
		}
	}
}

bool check(int cc){
	int i, j;
	i=list[cc-1]; j=list[cc];
	if(i<l1&&j>l1) return true;
	if(j<l1&&i>l1) return true;
	return false;
}

void process(){
	int i,j,k, rec=-1;
	Suffix_Sort();
	getHeight();
	ans=0;
/*	for(i=0; i<N; ++i){
		cout<<i<<' ';
		for(j=list[i]; j<N; ++j)
			cout<<S[j];
		cout<<endl;
	}*/
	
	for(i=1; i<N; ++i)
		if(Height[i]>ans&&check(i)){
			ans=Height[i];
		}
	printf("%d\n", ans);
}

int main(){
//	freopen("2774t.in", "r", stdin);
	while(scanf("%s%s", S1, S2)!=EOF){
//	scanf("%s%s", S1, S2);
		init();
		process();
	}
//	while(1);
	return 0;
}
	
