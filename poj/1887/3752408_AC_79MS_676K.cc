#include<iostream>
using namespace std;
int main()
{
	int h[33000],max,num[33000],a,i,j,test=0;
	while(cin>>a)
	{
		if(a==-1)
			break;
		test++;
		h[1]=a;
		num[1]=1;
		max=num[1];
		for(i=2;;i++)
		{
			cin>>h[i];
			num[i]=1;
			if(h[i]==-1)
				break;
			for(j=1;j<i;j++)
			{
				if(h[j]>=h[i])
					if(num[j]+1>num[i])
						num[i]=num[j]+1;
			}
			if(num[i]>max)
				max=num[i];
		}
		cout<<"Test #"<<test<<":"<<endl;
		cout<<"  maximum possible interceptions: "<<max<<endl;
		cout<<endl;
	}
}