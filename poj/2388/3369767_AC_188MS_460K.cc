#include <iostream>
using namespace std;

int n,a[100000];

void qsort(int s,int t){
	int x,i,j,k;
	x=a[(s+t)/2]; i=s; j=t;
	while(i<j){
		while(a[i]<x) i++;
		while(a[j]>x) j--;
		if(i<=j){
			k=a[i]; a[i]=a[j]; a[j]=k;
			i++; j--;
		}
	}
	if(s<j) qsort(s,j);
	if(i<t) qsort(i,t);
}

int main(){
	int i,j,k;
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i];
	qsort(1,n);
	if(n&1) cout<<a[n/2+1]<<endl;
	else cout<<a[n/2]<<endl;
	return 0;
}
