#include <stdio.h>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <set>
using namespace std;

int main(int argc, char** argv)
{
	srand(time(0));
	int n = atoi(argv[1]);
    multiset<int> s;

	printf("%d\n", n);
	for(int i=0; i<n; ++i)
	{
        int a = rand() % 6 + 1;
        int x = rand() % n + 1;
        printf("%d %d\n", a, x);
	}
	return 0;
}

