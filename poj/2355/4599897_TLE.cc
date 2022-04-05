#include <iostream>
using namespace std;

#define MAX 1000000010

int a[10001],l1,l2,l3,c1,c2,c3,n,i,j,k,s,t,f[10001]={0};

int getprice(int i,int j){
	int t;
	if(i>j){ t=i; i=j; j=t; }
	t=a[j]-a[i];
	if(t>0&&t<=l1) return c1;
	if(t<=l2) return c2;
	if(t<=l3) return c3;
	return MAX;
}

void process(){
	int i,j,k;
	
        if(s>t)
        {
            int tmp = s; s = t; t = tmp;
        }
        f[s]=0; 
	for(i=s+1;i<=t;i++){
		f[i]=getprice(i,s);
		for(j=s;j<i;j++)
			if(f[j]+getprice(i,j)<f[i])
				f[i]=f[j]+getprice(i,j);
        //cout<<i<<' '<<f[i]<<endl;
	}
	
	cout<<f[t]<<endl;
}

int main(){
    //freopen("2355.in", "r", stdin);
	scanf("%d%d%d%d%d%d",&l1,&l2,&l3,&c1,&c2,&c3);
	scanf("%d",&n);
	scanf("%d%d",&s,&t);
	a[1]=0;
	for(i=2;i<=n;i++) scanf("%d",&a[i]);
	process();
	return 0;
}

