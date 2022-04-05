#include <iostream>
#include <string>
using namespace std;

int n,m,eda[1000],edb[1000],e;
double dist[50],w[1000];
string s[4];

int find(string s1){
	int i;
	for(i=1;i<=n;i++)
		if(s[i]==s1)
			return i;
}

void init(){
	int i,j,a,b;
	double k;
	string s1,s2;
	for(i=1;i<=n;i++) cin>>s[i];
	cin>>m;
	e=0;
	for(i=1;i<=m;i++){
		cin>>s1>>k>>s2;
		a=find(s1); b=find(s2);
		e++;
		eda[e]=a; edb[e]=b; w[e]=k;
	}
}

void relax(int a,int b,double c){
	if(dist[a]*c>dist[b])
		dist[b]=dist[a]*c;
}

void process(){
	int i,j,k;
	for(i=1;i<=n;i++) dist[i]=0;
	dist[1]=1;
	for(i=1;i<n;i++)
		for(j=1;j<=e;j++)
			relax(eda[j],edb[j],w[j]);
	for(i=1;i<=e;i++)
		if(dist[eda[i]]*w[i]>dist[edb[i]]){
			cout<<"Yes"<<endl;
			return;
		}
	cout<<"No"<<endl;
}

int main(){
	int i,j,k;
	cin>>n;
	while(n!=0){
		init();
		process();
		cin>>n;
	}
	return 0;
}
