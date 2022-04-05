#include <iostream>
#include <algorithm>
#define MaxN 100010

using namespace std;

struct Node{
	int p, g;
}Cow[MaxN], Food[MaxN];

int N, M;
bool vis[MaxN];

bool cmp(Node A, Node B){
	return (A.p<B.p||(A.p==B.p&&A.g<B.g));
}

void init(){
	int i,j,k;
	scanf("%d%d", &N, &M);
	for(i=0; i<N; ++i) scanf("%d%d", &Cow[i].p, &Cow[i].g);
	for(i=0; i<M; ++i) scanf("%d%d", &Food[i].p, &Food[i].g);
	sort(Cow, Cow+N, cmp);
	sort(Food, Food+M, cmp);
	memset(vis, 0, sizeof vis);
	
//	cout<<"-------------"<<endl;
//	for(i=0; i<N; ++i) cout<<Cow[i].p<<' '<<Cow[i].g<<endl;
//	cout<<"-------------"<<endl;
//	for(i=0; i<M; ++i) cout<<Food[i].p<<' '<<Food[i].g<<endl;
//	cout<<"-------------"<<endl;

	
}

void process(){
	int i,j,k, pos=0, ans=0;
	for(i=0; i<N; ++i){
	//	pos=0;
		while(!(Food[pos].p>=Cow[i].p&&Food[pos].g>=Cow[i].g&&vis[pos]==0)){
			pos++;
			if(pos==M) break;
			
		}
		if(pos==M) break;
		ans+=Food[pos].p;
		vis[pos]=1;
		pos++;
		if(pos==M) break;
	}
	printf("%d\n", ans);
}

int main(){
	int i,j,k;
//	freopen("3622.in", "r", stdin);
	init();
	process();
//	while(1);
	return 0;
}
