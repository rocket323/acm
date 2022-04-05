#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;

struct Point
{
	int x, y;
	Point(int _x, int _y) : x(_x), y(_y){}
	Point() : x(0), y(0){}
};

Point ps, pe;
int l, u, r, d, ll, rr, uu, dd;

int cross(Point p1, Point p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

bool on_segment(Point p1, Point p2, Point p3)
{
	return min(p1.x, p2.x) <= p3.x && p3.x <= max(p1.x, p2.x)
		&& min(p1.y, p2.y) <= p3.y && p3.y <= max(p1.y, p2.y);
}

bool intersect(Point p1, Point p2, Point p3, Point p4)
{
	int d1 = cross(Point(p2.x-p1.x, p2.y-p1.y), Point(p3.x-p2.x, p3.y-p2.y));
	int d2 = cross(Point(p2.x-p1.x, p2.y-p1.y), Point(p3.x-p2.x, p3.y-p2.y));
	int d3 = cross(Point(p4.x-p3.x, p4.y-p3.y), Point(p1.x-p4.x, p1.y-p4.y));
	int d4 = cross(Point(p4.x-p3.x, p4.y-p3.y), Point(p2.x-p4.x, p2.y-p2.y));
	if(d1 * d2 < 0 && d3 * d4 < 0) return 1;

	if(d1 == 0 && on_segment(p1, p2, p3)) return 1;
	if(d2 == 0 && on_segment(p1, p2, p4)) return 1;
	if(d3 == 0 && on_segment(p3, p4, p1)) return 1;
	if(d4 == 0 && on_segment(p3, p4, p2)) return 1;

	return 0;
}

bool in(int l, int r, int d, int u, Point p)
{
	return l < p.x && p.x < r && d < p.y && p.y < u;
}

bool check()
{
	if(intersect(Point(l, d), Point(l, u), ps, pe)) return 1;
	if(intersect(Point(r, d), Point(r, u), ps, pe)) return 1;
	if(intersect(Point(l, d), Point(r, d), ps, pe)) return 1;
	if(intersect(Point(l, u), Point(r, u), ps, pe)) return 1;

	if(in(l, r, d, u, ps) && in(l, r, d, u, pe)) return 1;
	
	return 0;
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%d", &ps.x, &ps.y, &pe.x, &pe.y);
		scanf("%d%d%d%d", &ll, &uu, &rr, &dd);

		l = min(ll, rr), r = max(ll, rr);
		d = min(uu, dd), u = max(uu, dd);

		if(check()) puts("T");
		else puts("F");
	}
	return 0;
}

