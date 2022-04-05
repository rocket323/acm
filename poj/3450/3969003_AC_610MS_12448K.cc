#include <iostream>
#define MaxL 200000

using namespace std;

char S[MaxL], T[201];
int list[MaxL], tmp[MaxL], rank[MaxL], N, A[2][MaxL], b[MaxL];
int f[MaxL][20], P, map[MaxL], brd, cnt[MaxL], height[MaxL];
int L[MaxL];
int head[MaxL], next[MaxL];

bool cmp(int i, int j){
	return (S[i]<S[j]);
}

void init(){
	int i,j,k,pos=-1, len;
	N=0;
	strcpy(S, "");
	for(i=1; i<=P; ++i){
		gets(T);
		if(i>1){
			strcat(S, "$");
			map[++pos]=0;
		}
		strcat(S, T);
		len=strlen(T);
		for(j=pos+1; j<=pos+len; ++j)
			map[j]=i;
		pos+=len;
	}

	N=strlen(S);

	for(i=1; i<N; ++i){
		j=0;
		while((1<<j)<=i) j++;
		j--;
		L[i]=j;
	}

	for(i=0; i<N; ++i) list[i]=i;
	sort(list, list+N, cmp);
	b[list[0]]=0;
	for(i=1; i<N; ++i)
		if(S[list[i]]==S[list[i-1]]) b[list[i]]=b[list[i-1]];
		else b[list[i]]=i;
}

void Suffix_Sort(){
	int i,j,k, h;
	
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

int RMQ_ready(){
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

inline int Min(int a, int b){
	return (a<b)?a:b;
}

int LCP(int i, int j){
	int log=0;
	log=L[j-i+1];
	int k=j-(1<<log)+1;
	return Min(height[f[i][log]], height[f[k][log]]);
}

void process(){
	int i,j,k, ans=-MaxL, rec=-1;
	Suffix_Sort( );
	getHeight( );
	RMQ_ready( );
	int head=0, tail=0;
	memset(cnt, 0, sizeof cnt);
	brd=1;
	cnt[map[list[0]]]++;
	while(true){
		while(brd<P){
			tail++;
			if(tail==N) break;
			k=map[list[tail]];
			cnt[k]++;
			if(cnt[k]==1) brd++;
		}
		if(tail==N) break;
		k=LCP(head+1, tail);
		if(k>ans){
			ans=k;
			rec=list[head];
		}
		k=map[list[head]];
		cnt[k]--;
		if(cnt[k]==0) brd--;
		++head;
	}
	if(ans<=0) cout<<"IDENTITY LOST"<<endl;
	else{
		for(i=rec; i<rec+ans; ++i) cout<<S[i];
		cout<<endl;
	}
}

int main(){
	int i,j,k;
//	freopen("i.in", "r", stdin);
//	freopen("ii.out", "w", stdout);
	scanf("%d\n", &P);
	while(P!=0){
		init();
		process();
		scanf("%d\n", &P);
	}
//	while(1);
	return 0;
}
