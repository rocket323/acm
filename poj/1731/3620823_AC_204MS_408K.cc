#include <iostream>
#include <string>
#include <algorithm>
 
using namespace std;

int main()
{
	string str;
	while(cin>>str)
	{
		sort(&str[0],&str[0]+str.length());
		cout<<str<<endl;
		while(next_permutation(&str[0],&str[0]+str.length()))
		{
			cout<<str<<endl;
		}
	}
	return 0;
}