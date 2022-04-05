#include <iostream>
using namespace std;

int n,sum,ave,a[30];
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

bool process(int);

bool search(int board,int start, int curlen){
	if(board==4) return true;
	if(curlen==0) return process(board+1);
	if(start>n) return false;
	if(curlen<0) return false;
	
	
	int i;
	for(i=start;i<=n;i++)
		if(!used[i]){
			used[i]=true;
			if(search(board,i+1,curlen-a[i])) return true;
			used[i]=false;
		}
	return false;
}

bool process(int x){
	int i,j,k;
	for(i=1;i<=n;i++)
		if(!used[i]) break; 
			used[i]=true;
			if(search(x,i+1,ave-a[i])) return true;
			used[i]=false;
		
	return false;
}

bool check(){
	int j;
	if(sum%4!=0){
			return false;
	}
	for(j=1;j<=n;j++)
		if(a[j]>ave){
			return false;
		}
	return true;
}

int main(){
	int t,i,j,k;
	//freopen("2362.in","r",stdin);
	cin>>t;
	for(i=1;i<=t;i++){
		init();
		if(!check()){ cout<<"no"<<endl; continue; }
		memset(used,0,sizeof used);
		if(process(1)) cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}
	//while(k=1);
	return 0;
}
