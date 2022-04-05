#include <iostream>
#define MaxL 100000000
using namespace std;

struct Edage{
	int start, end;
	int weight;
}Mst[40];

int N,M,G[40][40], P, Max, ans;
char name[40][40];
bool vis[40], Find;

int getID(char s[]){
	int i;
	for(i=0;i<=N;i++)
		if(strcmp(name[i], s)==0) return i;
	N++;
	strcpy(name[N],s);
	return N;
}

void init(){
	int i,j,k,a,b;
	char s1[11], s2[11];
	scanf("%d",&M);
	strcpy(name[0], "Park");
	N=0;
	for(i=0;i<=20;i++)
		for(j=0;j<=20;j++)
			G[i][j]=MaxL;
	
	for(i=1;i<=M;i++){
		cin>>s1>>s2;
		a=getID(s1); b=getID(s2);
		cin>>G[a][b];
		G[b][a]=G[a][b];
	}
	N++;
	cin>>P;
}

void swap(int i, int j){
	int tmp;
	tmp=Mst[i].start; Mst[i].start=Mst[j].start; Mst[j].start=tmp;
	tmp=Mst[i].end; Mst[i].end=Mst[j].end; Mst[j].end=tmp;
	tmp=Mst[i].weight; Mst[i].weight=Mst[j].weight; Mst[j].weight=tmp;
}

int prim( ){
	int i,j,k, Min, rec, res=0, x, y;
	for(i=1;i<N-1;i++){
		Mst[i].start=1;
		Mst[i].end=i+1;
		Mst[i].weight=G[1][i+1];
	}
	for(i=1;i<N-1;i++){
		Min=MaxL;
		for(j=i;j<N-1;j++)
			if(Mst[j].weight<Min){
				rec=j;
				Min=Mst[j].weight;
			}
		swap(rec, i);
		x=Mst[rec].end;
		for(j=i+1;j<N-1;j++){
			y=Mst[j].end;
			if(G[x][y]<Mst[j].weight){
				Mst[j].start=x;
				Mst[j].weight=G[x][y];
			}
		}
		res+=Min;
	}
	return res;
}

void dfs(int now, int start, int &Max, int last, int &edg){
	int i;
	if(now==start){
		Find=true;
		return;
	}
	for(i=0;i<N-1;i++){
		if(Mst[i].start!=now&&Mst[i].end!=now) continue;
		if(Mst[i].start==now&&Mst[i].end!=now){
			dfs(Mst[i].end, start, Max, now, edg);
			if(Find){
				if(Max<Mst[i].weight&&Mst[i].end!=start){
					Max=Mst[i].weight;
					edg=i;
				}
				return;
			}
		}
		else if(Mst[i].start!=now&&Mst[i].end==now){
			dfs(Mst[i].start, start, Max, now, edg);
			if(Find){
				if(Max<Mst[i].weight&&Mst[i].start!=start){
					Max=Mst[i].weight;
					edg=i;
				}
				return;
			}
		}
	}
}

void process(){
	int i,j,k, Min, rec, MaxJ, MaxE, MaxEdge;
	ans=prim( );
	Min=MaxL+1;
	memset(vis, 0, sizeof vis);
	for(i=1;i<N;i++)
		if(G[0][i]<Min){
			Min=G[0][i];
			rec=i;
		}
	ans+=Min;
	vis[rec]=1;
	
	Mst[0].start=0;
	Mst[0].end=rec;
	Mst[0].weight=Min;
	
	for(i=2;i<=P;i++){
		Min=MaxL+1; Max=-1;
		MaxJ=-1; MaxE=-1;
		for(j=1;j<N;j++){
			if(vis[j]) continue;
			Find=0;
			Max=0;
			dfs(j, 0, Max, 0, MaxEdge);
			if(G[0][j]-Max<Min){
				Min=G[0][j]-Max;
				MaxE=MaxEdge;
				MaxJ=j;
			}
		}
		if(Min>=0) break;
		if(MaxE!=-1){
			Mst[MaxE].start=0;
			Mst[MaxE].end=MaxJ;
			Mst[MaxE].weight=G[0][MaxJ];
		}
		vis[j]=1;
		ans+=Min;
	}
	printf("Total miles driven: %d\n",ans);
}

int main(){
	int i,j,k;
//	freopen("1639.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
