#include <stdio.h>
#include <cstring>
#include <iostream>
#define maxl 500010
#define mod 1000000007
#define ll long long
using namespace std;

int n, b, k, x;
int a[maxl];

class Matrix
{
public:

	Matrix() : n(105), m(105)
	{
		memset(data, 0, sizeof data);
	}

	Matrix(int _n, int _m) : n(_n), m(_m)
	{
		memset(data, 0, sizeof data);
	}

	Matrix operator * (const Matrix& rhs)
	{
		Matrix c(n, rhs.m);
		for(int i = 0; i < c.n; ++i)
		{
			for(int j = 0; j < c.m; ++j)
			{
				for(int k = 0; k < c.m; ++k)
				{
					c.data[i][j] = (c.data[i][j] + (ll)data[i][k] * rhs.data[k][j] % mod) % mod;
				}
			}
		}
		return c;
	}

	Matrix& operator = (const Matrix& rhs)
	{
		n = rhs.n;
		m = rhs.m;
		for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) data[i][j] = rhs.data[i][j];
		return *this;
	}

	static Matrix Identity(int n)
	{
		Matrix c(n, n);
		for(int i = 0; i < n; ++i) c.data[i][i] = 1;
		return c;
	}

	int n, m;
	int data[105][105];
};

ostream& operator<<(ostream& out, const Matrix& matrix)
{
	for(int i = 0; i < matrix.n; ++i)
	{
		for(int j = 0; j < matrix.m; ++j)
		{
			out << matrix.data[i][j] << ' ';
		}
		out << endl;
	}
	return out;
}

void Init(Matrix& mat)
{
	for(int i = 0; i < x; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			int np = (i * 10 + a[j]) % x;;
			mat.data[i][np]++;
		}
	}
	//cout << "mat: \n" << mat << endl;
}

void Process(Matrix& mat)
{
	Matrix t = mat;
	Matrix ans = Matrix::Identity(x);

	//cout << "Identity: \n" << ans << endl;

	while(b)
	{
		if(b & 1) ans = ans * t;
		t = t * t;
		b >>= 1;
	}

	Matrix s(1, x);
	s.data[0][0] = 1;
	s = s * ans;

	cout << s.data[0][k] << endl;
}

int main()
{
	while(scanf("%d%d%d%d", &n, &b, &k, &x) != EOF)
	{
		for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
		Matrix mat(x, x);
		Init(mat);
		Process(mat);
	}

	return 0;
}

