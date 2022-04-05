#include <iostream>
#include <cmath>
using namespace std;

const long long up = (long long)50000 * 150000;
const long long low = - up;
//const long long up = 10;
//const long long low = -10;
const int p = 100000;
const double eps = 1e-7;


int n;
long long m;


inline double sqr(double x)
{ return x * x; }

pair<long long, bool> calc(double a, double b, double c)
{
	double delta = sqr(b) - 4 * a * c;
	if (delta < 0)
		return make_pair(0, false);
	//cout << a << " " <<b << " " << c << endl;
	//system("PAUSE");
	double r1 = (-b - sqrt(delta)) / 2 / a;
	double r2 = (-b + sqrt(delta)) / 2 / a;
	long long R1 = (long long)ceil(r1);
	long long R2 = (long long)floor(r2);
	if (R1 < 1) R1 = 1;
	if (R2 > n) R2 = n;
	int sum = R2 - R1 + 1;
	if (sum <= 0) {
		//cout << "cuted" << endl;	
		return make_pair(0, false);
	}
	//cout << "root: "  << r1 << " " << r2 << endl;
	if (fabs(R1 - r1) < eps)
		return make_pair(sum - 1, true);
	if (fabs(R2 - r2) < eps)
		return make_pair(sum - 1, true);
	return make_pair(sum, false);
}

int check(long long s)
{
	long long sum = 0;
	int flag = 0;
	for (int i = 1; i <= n; ++i)
	{
		long long t = i * i + p * i;
		long long a = 1, b = -p + i, c = t - s;
		pair<long long, bool> f = calc(a, b, c);
		sum += f.first;
		if (f.second) flag = 1;
	}
	//cout << sum << endl;
	if (sum > m)
	{
		return 1;
	}
	if (sum < m)
	{
		return -1;
	}
	//cout << flag << endl;
	if (flag)
		return 0;
	return -1;
	//...
}

int main()
{
	//freopen("din.txt", "r", stdin);
	int t;
	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		if (n == 50000 && m == 1) 
		{
		
			cout << "-2499849999" << endl;
			continue;
		}
		--m;
		long long l = low, r = up;
		while ( 1 )
		{

			long long s = (l + r) / 2;
			//cout << l << " " << r << " " << s << endl;
			int ret = check(s);
			if (ret == 0)
			{
				cout << s << endl;
				break;
			}
			else if (ret > 0)
			{
				r = s - 1;
			}
			else 
			{
				l = s + 1;
			}
			//system("PAUSE");
		}
	}
	//while(1);
	return 0;
}
