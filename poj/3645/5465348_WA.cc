#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;

char S[500];

double solve(double p)
{
	double ans = 0, a1, a2, p1, p2;

	char S1[500], S2[500], ch;
	cin >> S1;
	if(S1[0]=='(')
	{
		if(strlen(S1)==1) scanf("%lf", &p1);
		else sscanf(S1, "%c%lf", &ch, &p1);
		a1 = solve(p1);
	}
	else
	{
		sscanf(S1, "%lf", &p1);
		a1 = p1;
	}

	cin >> S2;

	if(S2[0]=='(')
	{
		if(strlen(S2)==1) scanf("%lf", &p2);
		else sscanf(S2, "%c%lf", &ch, &p2);
		a2 = solve(p2);
	}
	else
	{
		sscanf(S2, "%lf", &p2);
		a2 = p2;
	}

	ans = p * (a1 + a2) + (1 - p) * (a1 - a2);

	return ans;
}

int main()
{
	while(cin >> S)
	{
		
		if(S[0]=='(' && strlen(S)==2 && S[1]==')') break;
		if(S[0]!='(')
		{
			double k;
			sscanf(S, "%lf", &k);
			printf("%.2lf\n", k);
		}
		else
		{
			char ch;
			double p;
			if(strlen(S)==1) cin >> p;
			else sscanf(S, "%c%lf", &ch, &p);
			printf("%.2lf\n", solve(p));
		}
	}
	return 0;
}
