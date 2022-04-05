#include <iostream>
#include <algorithm>
#define MaxN 100010
using namespace std;

char S[MaxN+MaxN];
int list[MaxN], rank[MaxN];
int head[MaxN], next[MaxN], b[MaxN];
int Height[MaxN], l1, l2;
int N, ans;

void init(){
	int i,j,k;
	scanf("%s", S);
	l1=strlen(S);
	S[l1]='$';
	scanf("%s", S+l1+1);
	l2=strlen(S+l1+1);
	N=l1+1+l2;
}

bool cmp(const int & i, const int & j){
	return S[i]<S[j];
}

void Suffix_Sort(){
	int i,j,k, h;
	for(i=0; i<N; ++i) list[i]=i;
	sort(list, list+N, cmp);
	b[list[0]]=0;
	for(i=1; i<N; ++i)
		if(S[list[i]]==S[list[i-1]]) b[list[i]]=b[list[i-1]];
		else b[list[i]]=b[list[i-1]]+1;
	
	for(h=1; h<N; h<<=1){
		for(i=0; i<N; ++i) head[i]=next[i]=-1;
		for(i=N-1; i>=0; --i)
			if(list[i]){
				j=list[i]-h; if(j<0) j+=N;
				next[j]=head[b[j]]; head[b[j]]=j;
			}
		j=N-h; next[j]=head[b[j]]; head[b[j]]=j;
		for(i=k=0; i<N; ++i) if(head[i]>=0)
			for(j=head[i]; j>=0; j=next[j]) list[k++]=j;
		for(i=0; i<N; ++i) if(i>0&&list[i]+h<N&&list[i-1]+h<N&&b[list[i]]==b[list[i-1]]&&b[list[i]+h]==b[list[i-1]+h])
			rank[list[i]]=rank[list[i-1]];
			else rank[list[i]]=i;
		for(i=0; i<N; ++i) b[i]=rank[i];
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
	return ((list[cc-1]-l1)*(list[cc]-l1)<0);
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
//	freopen("2774.in", "r", stdin);
//	while(scanf("%s%s", S1, S2)!=EOF){
		init();
		process();
//	}
//	while(1);
	return 0;
}

	
