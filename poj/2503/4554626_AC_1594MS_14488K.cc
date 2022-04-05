#include <iostream>
#include <sstream>
#include <map>
using namespace std;

map<string, string> m;

void process()
{
    char S[100], a[100], b[100];
    gets(S);
    while(S[0])
    {
        sscanf(S, "%s%s", a, b);
        m.insert(make_pair(b, a));
        gets(S);
    }

    while(gets(S))
    {
        if(m.find(S)!=m.end())
            printf("%s\n", m[S].c_str());
        else
            printf("eh\n");
    }
}

int main()
{
    process();
    return 0;
}

