#include <iostream>
using namespace std;

struct node{
	int d, lev;
}A[11];

int N, D[11], rec, sum;
int G[11][11], S[11];
bool vis[11];

void init(){
	int i,j,k;
	cin>>N;
	sum=0;
	for(i=1;i<=N;i++){
		cin>>A[i].d;
		A[i].lev=i;
	}
}

void swap(int i, int j){
	int tmp;
	tmp=A[i].d; A[i].d=A[j].d; A[j].d=tmp;
	tmp=A[i].lev; A[i].lev=A[j].lev; A[j].lev=tmp;
}

void out( ){
	int i,j;
	cout<<"YES\n";
	for(i=1;i<=N;i++){
		for(j=1;j<N;j++) cout<<G[i][j]<<' ';
		cout<<G[i][N]<<endl;
	}
	cout<<endl;
}

bool work(int N){
	int i,j,k,tmp,s,e;
	if(N==1) return A[1].d==0;
	
	for(i=1;i<N;i++)
		for(j=i+1;j<=N;j++)
			if(A[i].d<A[j].d)
				swap(i, j);
	for(i=1;i<=A[N].d;i++){
		s=A[i].lev; e=A[N].lev;
		G[s][e]=1; G[e][s]=1;
		A[i].d--;
	}
	return work(N-1);
}

void process(){
	int i,j,k;
	memset(G, 0, sizeof G);
	if(!work(N)){
		cout<<"NO\n\n";
	}
	else out( );
}

int main(){
	int i,j,k,T;
//	freopen("1659.in","r",stdin);
	cin>>T;
	for(i=1;i<=T;i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
