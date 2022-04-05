#include <iostream>
using namespace std;

int n,sum,ave,a[30],s[30];

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

bool search(int x,int l1,int l2,int l3,int l4){
	if(l1>ave||l2>ave||l3>ave||l4>ave) return false;
	if(l1==ave&&l2==ave&&l3==ave&&l4==ave) return true;
	if(x>n) return false;
	if(search(x+1,l1+a[x],l2,l3,l4)) return true;
	if(search(x+1,l1,l2+a[x],l3,l4)) return true;
	if(search(x+1,l1,l2,l3+a[x],l4)) return true;
	if(search(x+1,l1,l2,l3,l4+a[x])) return true;
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
	flag=search(1,0,0,0,0);
	if(flag) cout<<"yes"<<endl;
	else cout<<"no"<<endl;
}

int main(){
	int t,i,j,k;
	cin>>t;
	for(i=1;i<=t;i++){
		init();
		process();
	}
	return 0;
}
