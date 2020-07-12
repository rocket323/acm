#include <stdio.h>
#include <vector>
#include <assert.h>
using namespace std;

const double alpha = 0.7;
const int maxl = 1000010;

struct node {
    node *ch[2];
    int key;
    int size, cover; // 有效节点数，总节点数
    bool exist;

    void pushUp() {
        size = ch[0]->size + ch[1]->size + (int)exist;
        cover = ch[0]->cover + ch[1]->cover + 1;
    }
    bool isBad() {
        return (ch[0]->cover > cover * alpha + 5 ||
                ch[1]->cover > cover * alpha + 5);
    }
};

class Stree {
private:
    node memo[maxl];
    node *tail, *root, *null;

    node *newNode(int key) {
        node *p = tail++;
        p->ch[0] = p->ch[1] = null;
        p->size = p->cover = 1;
        p->exist = true;
        p->key = key;
        return p;
    }
    node **insert(node *&p, int val) {
        if (p == null) {
            p = newNode(val);
            return &null;
        } else {
            p->size++; p->cover++;
            node **res = insert(p->ch[val >= p->key], val);
            if (p->isBad())
                res = &p;
            return res;
        }
    }
    void erase(node *p, int id) {
        if (p == null) return;
        int offset = p->ch[0]->size + p->exist;
        if (p->exist && id == offset) {
            p->size--;
            p->exist = false;
            return;
        } else {
            if (id <= offset) erase(p->ch[0], id);
            else erase(p->ch[1], id - offset);
            p->pushUp();
        }
    }
    void travel(node *p, vector<node *> &v) {
        if (p == null) return;
        travel(p->ch[0], v);
        if (p->exist)
            v.push_back(p);
        travel(p->ch[1], v);
    }
    node *divide(vector<node *> &v, int l, int r) {
        if (l >= r) return null;
        int mid = (l + r) >> 1;
        node *p = v[mid];
        p->ch[0] = divide(v, l, mid);
        p->ch[1] = divide(v, mid + 1, r);
        p->pushUp();
        return p;
    }
    void rebuild(node *&p) {
        static vector<node *> v;
        v.clear();
        travel(p, v);
        p = divide(v, 0, v.size());
    }

public:
    Stree() {
        tail = memo;
        null = tail++;
        null->ch[0] = null->ch[1] = null;
        null->cover = null->size = null->key = null->exist = 0;
        root = null;
    }
    int Rank(int val) {
        int ans = 1;
        for (node *now = root; now != null; ) {
            if (now->key >= val) now = now->ch[0];
            else {
                ans += now->ch[0]->size + now->exist;
                now = now->ch[1];
            }
        }
        return ans;
    }
    int Kth(int k) {
        if (k <= 0 || k > root->size)
            return -1;
        for (node *now = root; now != null; ) {
            if (now->ch[0]->size + 1 == k && now->exist)
                return now->key;
            else if (now->ch[0]->size >= k)
                now = now->ch[0];
            else {
                k -= now->ch[0]->size + now->exist;
                now = now->ch[1];
            }
        }
    }
    void Insert(int val) {
        node **p = insert(root, val);
        if (*p != null) rebuild(*p);
    }
    void Erase(int k) {
        if (root->size == 0)
            return;
        erase(root, Rank(k));
        if (root->size < alpha * root->cover)
            rebuild(root);
    }
    void EraseKth(int k) {
        erase(root, k);
        if (root->size < alpha * root->cover)
            rebuild(root);
    }
};

Stree tree;
int main()
{
    int n, a, x;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a, &x);
        switch (a) {
        case 1: tree.Insert(x); break;
        case 2: tree.Erase(x); break;
        case 3: printf("%d\n", tree.Rank(x)); break;
        case 4: printf("%d\n", tree.Kth(x)); break;
        case 5: printf("%d\n", tree.Kth(tree.Rank(x) - 1)); break;
        case 6: printf("%d\n", tree.Kth(tree.Rank(x + 1))); break;
        }
    }

    return 0;
}

