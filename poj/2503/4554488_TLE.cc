#include <iostream>
#include <sstream>
#include <map>
using namespace std;

map<string, string> m;

void process()
{
    string S;
    getline(cin, S);
    while(S[0])
    {
        istringstream in(S);
        string a, b;
        in>>a;
        in>>b;
        m[b] = a;
        getline(cin, S);
    }

    while(cin>>S)
    {
        if(m.find(S)!=m.end())
            cout<<m[S]<<endl;
        else
            printf("eh\n");
    }
}

int main()
{
    //freopen("2503.in", "r", stdin);
    process();
    return 0;
}

