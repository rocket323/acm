#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a[100001],d[100001],n,len;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    d[1]=a[1];
    len=1;
    for(int i=2;i<=n;i++)
    {
        if(a[i]>=d[len])
        d[++len]=a[i];
        else
        {
            int j=upper_bound(d+1,d+len+1,a[i])-d;
            d[j]=a[i];
        }
    }
    cout<<len<<endl;
    return 0;
}
