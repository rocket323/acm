#include<iostream>
using namespace std;

int main()
{
//	freopen("1017.in", "r", stdin);
//	freopen("std.out", "w", stdout);
	int a[7],sum;
	cin>>a[1]>>a[2]>>a[3]>>a[4]>>a[5]>>a[6];
	while(a[1]!=0||a[2]!=0||a[3]!=0||a[4]!=0||a[5]!=0||a[6]!=0)
    {
	sum=0;
	if(a[6]!=0) sum+=a[6];
	if(a[5]!=0) 
	{ sum+=a[5];
	  if(a[1]>0)
	  a[1]=a[1]-11*a[5];
	  if(a[1]<0) a[1]=0;
	}
	if(a[4]!=0)
	{ sum+=a[4];
	  if(a[1]>0)
	  { if(a[4]*5-a[2]>0)
	       a[1]=a[1]-4*(a[4]*5-a[2]);
	    if(a[1]<0) a[1]=0;
	  }
	  if(a[2]>0)
	  a[2]=a[2]-5*a[4];
	  if(a[2]<0) a[2]=0;
	}
	if(a[3]!=0)
	{  sum+=a[3]/4;
	   if(a[3]%4!=0) sum++;
	   if(a[1]>0)
		   if(a[3]%4!=0)
		   { if(a[3]%4==1)
                if(a[2]<=5) a[1]=a[1]-27-a[2]*4;
				else a[1]=a[1]-7;
			if(a[3]%4==2)
                if(a[2]<=3) a[1]=a[1]-18-a[2]*4;
				else a[1]=a[1]-6;
			if(a[3]%4==3)
                if(a[2]<=1) a[1]=a[1]-9-a[2]*4;
				else a[1]=a[1]-5;
		   }
       if(a[1]<0) a[1]=0;
	   if(a[2]>0)
	     if(a[3]%4!=0)
		 { if(a[3]%4==1)
		      a[2]=a[2]-5;
		   else if(a[3]%4==2)
			       a[2]=a[2]-3;
		   else   
			   a[2]=a[2]-1;
		 }
	   if(a[2]<0) a[2]=0;
	 }
	 if(a[2]!=0)
	 { sum+=a[2]/9;
	   if(a[2]%9!=0) sum++;
	   if(a[1]>0)
	      if(a[2]%9!=0)
		     a[1]=a[1]-36+4*(a[2]%9);
	   if(a[1]<0) a[1]=0;
	 }
	 if(a[1]!=0)
	 { sum+=a[1]/36;
	   if(a[1]%36!=0) sum++;
	 }
	 cout<<sum<<endl;
	 cin>>a[1]>>a[2]>>a[3]>>a[4]>>a[5]>>a[6];
	}
//	while(1);
	return 0;
}
