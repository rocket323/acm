#include <stdio.h>
#include <math.h>
#include <vector>
#include <iomanip>
#include <iostream>
using namespace std;

class Node
{
public:
	Node(string str, long double val)
	{
		m_str = str;
		m_val = val;
	}

	string m_str;
	long double m_val;
};

long double x, y, z;

int main()
{
	while(cin >> x >> y >> z)
	{
		vector<Node> v;
		v.push_back(Node("x^y^z", log(x) * pow(y, z) ));
		v.push_back(Node("x^z^y", log(x) * pow(z, y) ));
		v.push_back(Node("(x^y)^z", log(x) * y * z ));
		v.push_back(Node("(x^z)^y", log(x) * y * z ));

		v.push_back(Node("y^x^z", log(y) * pow(x, z) ));
		v.push_back(Node("y^z^x", log(y) * pow(z, x) ));
		v.push_back(Node("(y^x)^z", log(y) * x * z ));
		v.push_back(Node("(y^z)^x", log(y) * x * z ));

		v.push_back(Node("z^x^y", log(z) * pow(x, y) ));
		v.push_back(Node("z^y^x", log(z) * pow(y, x) ));
		v.push_back(Node("(z^x)^y", log(z) * x * y ));
		v.push_back(Node("(z^y)^x", log(z) * x * y ));

		int idx = -1;
		for(int i = 0; i < (int)v.size(); ++i)
		{
			//printf("%d: %s, %Lf\n", i, v[i].m_str.c_str(), v[i].m_val);
			//cout << i << ' '  << v[i].m_str << ' ' << v[i].m_val << endl;
			if(idx == -1 || v[i].m_val > v[idx].m_val) idx = i;
		}
		//cout << "xx: " << pow(x, z) << ' '  << pow(z, x) << endl;
		printf("%s\n", v[idx].m_str.c_str());
		//cout << "yy: " << sizeof(long double) << ' ' << sizeof(double) << endl;
	}

	return 0;
}

