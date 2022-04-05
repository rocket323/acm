#include <iostream>
using namespace std;

int n,sum,ave,a[30],s[30];
bool used[30];

void init(){
	int i,j,k;
	cin>>n;
	sum=0;
	for(i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
		ave=sum/4;
	}
	for(i=1;i<n;i++)
		for(j=i+1;j<=n;j++)
			if(a[i]<a[j]){
				k=a[i]; a[i]=a[j]; a[j]=k;
			}
}

bool search(int board, int curlen){
	if(board==4&&curlen==0) return true;
	//if(stick>n) return false;
	if(curlen<0) return false;
	if(curlen==0) return search(board+1,ave);
	
	int i;
	for(i=1;i<=n;i++)
		if(!used[i]){
			used[i]=true;
			if(search(board,curlen-a[i])) return true;
			used[i]=false;
		}
	return false;
}

void process(){
	int i,j,k;
	bool flag;
	if(sum%4!=0){
		cout<<"no"<<endl;
		return;
	}
	for(i=1;i<=n;i++)
		if(a[i]>ave){
			cout<<"no"<<endl;
			return;
		}
	memset(used,0,sizeof used);
	flag=search(1,ave);
	if(flag) cout<<"yes"<<endl;
	else cout<<"no"<<endl;
}

int main(){
	int t,i,j,k;
	//freopen("2362.in","r",stdin);
	cin>>t;
	for(i=1;i<=t;i++){
		init();
		process();
	}
//	while(k=1);
	return 0;
}
