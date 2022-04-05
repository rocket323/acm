#include <iostream>
#define DE 600
using namespace std;

int dx[4]={1,0,-1,0},dy[4]={0,1,0,-1};
bool vis[1301][1301];
int Sx[3000000], Sy[3000000], St[3000000], head, tail,X,Y,N;

void init(){
	int i,j,k,a,b;
	memset(vis,0,sizeof vis);
	scanf("%d%d%d",&X,&Y,&N);
	X+=DE; Y+=DE;
	for(i=1;i<=N;i++){
		scanf("%d%d",&a,&b);
		vis[a+DE][b+DE]=1;
	}
}

void work(){
	int i,j,k;
	for(k=0;k<4;k++){
		i=Sx[head]+dx[k]; j=Sy[head]+dy[k];
		if(i>=0&&i<=1200&&j>=0&&j<=1200)
			if(!vis[i][j]){
				tail++;
				Sx[tail]=i; Sy[tail]=j;
				St[tail]=St[head]+1;
				vis[i][j]=true;
			}
	}
}

void process(){
	int i,j,k;
	head=1; tail=1;
	Sx[1]=600; Sy[1]=600; St[1]=0;
	while(head<=tail){
		if(Sx[head]==X&&Sy[head]==Y){
			printf("%d\n",St[head]);
			break;
		}
		work();
		head++;
	}
}

int main(){
	int i,j,k;
//	freopen("3626.in","r",stdin);
	init();
	process();
//	while(k=1);
	return 0;
}
