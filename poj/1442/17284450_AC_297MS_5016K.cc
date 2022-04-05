#include <stdio.h>
#include <vector>
#include <cstring>
#include <assert.h>
using namespace std;

const double alpha = 0.7;
const int maxl = 1000010;

struct node {
    node *p, *ch[2];
    int key, size;

    bool getlr() {
        return p->ch[1] == this;
    }
    node *link(int w, node *p) {
        ch[w] = p;
        if (p) p->p = this;
        return this;
    }
    void update() {
        size = 1 + (ch[0] ? ch[0]->size : 0) + (ch[1] ? ch[1]->size : 0);
    }
};

class SplayTree {
public:
    node memo[maxl], *tail, *null, *root;

    SplayTree() {
        root = NULL;
        tail = memo;
    }

    node *newNode(int key) {
        node *p = tail++;
        p->ch[0] = p->ch[1] = NULL;
        p->size = 1; p->p = NULL;
        p->key = key;
        return p;
    }
    void rot(node *p) {
        node *q = p->p->p;
        if (p->getlr())
            p->link(0, p->p->link(1, p->ch[0]));
        else
            p->link(1, p->p->link(0, p->ch[1]));
        p->p->update();
        if (q)
            q->link(q->ch[1] == p->p, p);
        else {
            p->p = 0;
            root = p;
        }
    }
    void splay(node *p, node *tar) {
        while (p->p != tar && p->p->p != tar) {
            if (p->getlr() == p->p->getlr())
                rot(p->p), rot(p);
            else
                rot(p), rot(p);
        }
        if (p->p) rot(p);
        p->update();
    }
    void Insert(int val) {
        node *p = root, *q = NULL;
        while (p) {
            q = p;
            p = p->ch[val >= p->key];
        }
        p = newNode(val);
        if (!q) {
            root = p;
            return;
        }
        q->link(val >= q->key, p);
        q->update();
        splay(p, 0);
    }
    node *Kth(int k) {
        node *p = root;
        int w = p->ch[0] ? p->ch[0]->size : 0;
        while (w + 1 != k) {
            if (w >= k) p = p->ch[0];
            else {
                k -= w + 1;
                p = p->ch[1];
            }
            w = p->ch[0] ? p->ch[0]->size : 0;
        }
        splay(p, 0);
        return p;
    }
};

SplayTree tree;
int a[maxl], b[maxl], x, n, m;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    memset(b, 0, sizeof b);
    for (int i = 0; i < m; ++i) {
        scanf("%d", &x);
        b[x]++;
    }

    int p = 0;
    for (int i = 1; i <= n; ++i) {
        tree.Insert(a[i]);
        for (int j = 0; j < b[i]; ++j) {
            p++;
            printf("%d\n", tree.Kth(p)->key);
        }
    }

    return 0;
}
