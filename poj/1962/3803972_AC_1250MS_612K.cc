#include <iostream>
#include <cmath>
#define MaxN 20001
#define Mod 1000
using namespace std;

int pre[MaxN], N, len[MaxN];

int find(int now){
	if(pre[now]==now) return now;
	int ans=find(pre[now]);
	
	len[now]=(len[pre[now]]+len[now]);
	
	pre[now]=ans;
	return ans;
}

void process(){
	int i,j,k, a, b, x, y, ans;
	char ch;
	cin>>N;
	cin>>ch;
	for(i=1; i<=N; i++){ pre[i]=i; len[i]=0; }
	while(ch!='O'){
		if(ch=='E'){
			cin>>a;
		//	if(a==3) cout<<"hi "<<len[a]<<' '<<pre[a]<<' '<<pre[2]<<endl;
			x=find(a);
			cout<<len[a]<<endl;
			
		}
		else if(ch=='I'){
			cin>>a>>b;
			pre[a]=b;
			
			len[a]=abs(a-b)%Mod;
		//	if(a==2) cout<<"hi "<<len[a]<<endl;
		}
		cin>>ch;
	}
}

int main(){
	int i,j,k,T;
//	freopen("1962.in","r",stdin);
	scanf("%d",&T);
	for(i=1; i<=T; i++){
		process();
	}
//	while(k=1);
	return 0;
}
