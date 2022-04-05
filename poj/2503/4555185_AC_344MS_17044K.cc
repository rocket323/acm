#include <iostream>
#include <malloc.h>
using namespace std;

struct node
{
    char w[11];
    node* sub[26];
};

node* root;

node* newNode(char S[])
{
    node* tmp = (node*)malloc(sizeof(node));
    strcpy(tmp->w, S);
    for(int i=0; i<26; ++i)
        tmp->sub[i] = NULL;
    return tmp;
}

void insert(node* now, char b[], int pos, int len, char a[])
{
    int k = b[pos]-'a';

    if(pos==len-1)
    {
        if(now->sub[k]==NULL)
            now->sub[k] = newNode(a);
        else strcpy(now->sub[k]->w, a);
        return;
    }

    if(now->sub[k]==NULL)
        now->sub[k] = newNode("");
    
    insert(now->sub[k], b, pos+1, len, a);
}

char* find(node* now, char a[], int pos, int len)
{
    int k = a[pos]-'a';
    if(now->sub[k]==NULL) return "";
    if(pos==len-1)
        return now->sub[k]->w;
    
    return find(now->sub[k], a, pos+1, len);
}

void init()
{
    root = newNode("");

    char S[100], a[11], b[11];
    while(gets(S), S[0])
    {
        sscanf(S, "%s%s", a, b);
        insert(root, b, 0, strlen(b), a);
    }
    
    while(gets(S))
    {
        char* res = find(root, S, 0, strlen(S));
        if(strcmp(res, "")==0) puts("eh");
        else puts(res);
    }
}

int main()
{
    init();
    return 0;
}

