#include <iostream>
#include <algorithm>
#define MaxN 20010
using namespace std;

int N, P, S[MaxN], b[MaxN], rank[MaxN];
int list[MaxN], head[MaxN], next[MaxN];
int height[MaxN], f[MaxN][15], Log[MaxN];

bool cmp(int i, int j){
	return (S[i]<S[j]);
}

void suffixSort(){
	int i,j,k, h;
	
	for(i=0; i<N; ++i) list[i]=i;
	sort(list, list+N, cmp);
	b[list[0]]=0;
	for(i=1; i<N; ++i)
		if(S[list[i]]==S[list[i-1]]) b[list[i]]=b[list[i-1]];
		else b[list[i]]=i;
	
	for(h=1; h<N; h<<=1){
		for(i=0; i<N; ++i) head[i]=next[i]=-1;
		for(i=N-1; i>=0; --i)
			if(list[i]){
				j=list[i]-h; if(j<0) j+=N;
				next[j]=head[b[j]]; head[b[j]]=j;
			}
		j=N-h; next[j]=head[b[j]]; head[b[j]]=j;
		for(i=k=0; i<N; ++i)
			if(head[i]>=0)
				for(j=head[i]; j>=0; j=next[j]) list[k++]=j;
		for(i=0; i<N; ++i)
			if(i>0&&list[i]+h<N&&list[i-1]+h<N&&b[list[i]]==b[list[i-1]]
				&&b[list[i]+h]==b[list[i-1]+h])
					rank[list[i]]=rank[list[i-1]];
			else rank[list[i]]=i;
		for(i=0; i<N; ++i) b[i]=rank[i];
	}
}

void getHeight(){
	int i,j,k, h;
	height[0]=0;
	for(i=0; i<N; ++i) rank[list[i]]=i;
	for(h=0, i=0; i<N; ++i)
		if(rank[i]>0){
			j=list[rank[i]-1];
			while(S[i+h]==S[j+h]) ++h;
			height[rank[i]]=h;
			if(h>0) --h;
		}
}

void rmqReady(){
	int i,j,k;
	for(i=0; i<N; ++i) f[i][0]=i;
	for(j=1; (1<<j)<=N; ++j){
		for(i=0; i+(1<<j)-1<N; ++i){
			k=i+(1<<(j-1));
			if(height[f[i][j-1]]<height[f[k][j-1]])
				f[i][j]=f[i][j-1];
			else f[i][j]=f[k][j-1];
		}
	}
}

int Min(int a, int b){
	return (a<b)?a:b;
}

int LCP(int i, int j){
	int l=Log[j-i+1];
	int k=j-(1<<l)+1;
	return Min(height[f[i][l]], height[f[k][l]]);
}

void init(){
	int i,j,k;
	scanf("%d%d", &N, &P);
	for(i=0; i<N; ++i) scanf("%d", &S[i]);
	
	for(i=0; i<N; ++i){
		j=0;
		while((1<<j)<=i) j++;
		j--;
		Log[i]=j;
	}
	suffixSort();
	getHeight();
	rmqReady();
}

void process(){
	int i,j,k, ans=0;

	for(i=1; i<=N-P+1; ++i){
		if(LCP(i, i+P-2)>ans){
			ans=LCP(i, i+P-2);
		}
	}
	printf("%d\n", ans);

}

int main(){
//	freopen("patterns.1.in", "r", stdin);
//	freopen("patterns.1.out", "w", stdout);
//	freopen("oo.out", "w", stdout);
	init();
	process();
//	while(1);
	return 0;
}
