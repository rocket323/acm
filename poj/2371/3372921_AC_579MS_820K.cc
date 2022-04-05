#include <iostream>
using namespace std;

int a[1000000],q[100000],k,n;

void qsort(int s,int t){
	int x,i,j,tmp;
	x=a[s+rand()%(t-s+1)]; i=s; j=t;
	while(i<j){
		while(a[i]<x) i++;
		while(a[j]>x) j--;
		if(i<=j){
			tmp=a[i]; a[i]=a[j]; a[j]=tmp;
			i++; j--;
		}
	}
	if(s<j) qsort(s,j);
	if(i<t) qsort(i,t);
}

int main(){
	int i,j;
	char ch;
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i];
	cin>>ch>>ch>>ch;
	cin>>k;
	for(i=1;i<=k;i++) cin>>q[i];
	qsort(1,n);
	for(i=1;i<=k;i++) cout<<a[q[i]]<<endl;
	return 0;
}
	
