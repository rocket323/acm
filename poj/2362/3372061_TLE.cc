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
			if(a[i]>a[j]){
				k=a[i]; a[i]=a[j]; a[j]=k;
			}
}

bool search(int x,int l1,int l2,int l3,int l4){
	//if(l1>ave||l2>ave||l3>ave||l4>ave) return false;
	//if(l1==ave&&l2==ave&&l3==ave&&l4==ave) return true;
	//if(a[x]>l1||a[x]>l2||a[x]>l3||a[x]>l4) return false;
	//if(a[n]>l1&&a[n]>l2&&a[n]>l3&&a[n]>l4) return false;
	if(l1==0&&l2==0&&l3==0&&l4==0) return true;
	if(x>n) return false;
	if(a[x]<=l1||l1==0&&a[x]<=l2||l2==0&&a[x]<=l3||l3==0&&a[x]<=l4||l4==0){
		if(a[n]<=l1||a[n]<=l2||a[n]<=l3||a[n]<=l4){
			if(search(x+1,l1-a[x],l2,l3,l4)) return true;
			if(search(x+1,l1,l2-a[x],l3,l4)) return true;
			if(search(x+1,l1,l2,l3-a[x],l4)) return true;
			if(search(x+1,l1,l2,l3,l4-a[x])) return true;
		}
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
	flag=search(1,ave,ave,ave,ave);
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
	//while(k=1);
	return 0;
}
