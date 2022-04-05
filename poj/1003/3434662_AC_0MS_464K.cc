#include <iostream>
#include<math.h>
using namespace std;
int main()
{
     float c,n,p;
     cin>>c; 
     while(c!=0)
	   {for(n=1,p=0;p<c;n++)p=p+(1/(n+1));
	   cout<<(n-1)<<" "<<"card(s)\n";cin>>c;}
}
