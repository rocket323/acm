#include <iostream>
#define Max 10000000
using namespace std;

int n,m,id[30],g[30][30],st[30],t,save[30];

int tp(){
	int x,i,j,k,rec,cnt=0,ans;
	bool error=false;
	t=0;
	memcpy(save,id,sizeof id);
	for(x=1;x<=n;x++){
		cnt=0;
		for(i=1;i<=n;i++)
			if(id[i]==0){
				cnt++;
				rec=i;
			}
		if(cnt==0){
			memcpy(id,save,sizeof save);
			return -1;
		}
		if(cnt>1){
			error=true;
		}
		for(i=1;i<=n;i++)
			if(g[rec][i]==1)
				id[i]--;
		id[rec]=Max;
		t++;
		st[t]=rec;
	}
	memcpy(id,save,sizeof save);
	if(error) return 0;
	return 1;
}

void process(){
	int i,j,k,a,b;
	char c1,c2,ch;
	memset(g,0,sizeof g);
	memset(id,0,sizeof id);
	for(i=1;i<=m;i++){
		cin>>c1>>ch>>c2;
		//cout<<c1<<ch<<c2<<endl;
		a=c1-'A'+1; b=c2-'A'+1;
		id[a]++;
		g[b][a]=1;
		k=tp();
		//if(i==4) for(j=1;j<=n;j++) cout<<j<<' '<<id[j]<<endl;
		if(k==1){
			printf("Sorted sequence determined after %d relations: ",i);
			for(j=t;j>0;j--) cout<<(char)(st[j]+'A'-1);
			cout<<'.'<<endl;
			for(j=i+1;j<=m;j++) cin>>c1>>ch>>c2;
			return;
		}
		else if(k==-1){
			printf("Inconsistency found after %d relations.\n",i);
			for(j=i+1;j<=m;j++) cin>>c1>>ch>>c2;
			return;
		}
	}
	printf("Sorted sequence cannot be determined.\n");
	//for(i=1;i<=n;i++) cout<<i<<' '<<id[i]<<endl;
}

int main(){
	int i,j,k;
	cin>>n>>m;
	while(n!=0){
		process();
		cin>>n>>m;
	}
	return 0;
}
