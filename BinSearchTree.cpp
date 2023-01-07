#include <iostream>
#include <stack>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v;
        nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    void Ramas();
    void Hojas();
    void Hijos();
    void Hermanos();
private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* x);
    void InOrderRamas(CBinNode* x);
    void InOrderHojas(CBinNode* x);
    void InOrderHijos(CBinNode* x);
    void InOrderHermanos(CBinNode* x);
    CBinNode* root;
    bool brep;
};

CBinTree::CBinTree()
{
    root = 0;
    brep = 0;
}

CBinTree::~CBinTree()
{
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for ( p = &root;
         *p && (*p)->value != x;
         p = &((*p)->nodes[ (*p)->value < x ]) );
    return *p != 0;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinNode(x);
    return 1;
}

bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if ( !Find(x,p) ) return 0;
 
    if ( (*p)->nodes[0] && (*p)->nodes[1] ) //case 2
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    // case 0 or case 1
    CBinNode* t = *p;
    *p = (*p)->nodes[ (*p)->nodes[1] != 0 ];
    delete t;
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** p)
{
    CBinNode** q = p;
    for ( q = &((*q)->nodes[!brep]); *q; q = &((*q)->nodes[brep]) );
    brep = !brep;
    return q;
}

void CBinTree::InOrder(CBinNode* x)
{
    if ( !x ) return;
    InOrder(x->nodes[0]);
    std::cout << x->value << ' ';
    InOrder(x->nodes[1]);
}

void CBinTree::InOrderRamas(CBinNode* x)
{
    if (!x) return;
    InOrderRamas(x->nodes[0]);
    if (x->nodes[0] || x->nodes[1])
        std::cout << x->value << ' ';
    InOrderRamas(x->nodes[1]);
}

void CBinTree::InOrderHojas(CBinNode* x)
{
    if (!x) return;
    InOrderHojas(x->nodes[0]);
    if (!(x->nodes[0] || x->nodes[1]))
        std::cout << x->value << ' ';
    InOrderHojas(x->nodes[1]);
}

void CBinTree::InOrderHijos(CBinNode* x)
{
    if (!x) return;
    if (x->nodes[0] || x->nodes[1])
    {
        std::cout << '(' << x->value << ", ";
        if (x->nodes[0] && x->nodes[1])
            std::cout << x->nodes[0]->value << " y " << x->nodes[1]->value << ") ";
        else
            std::cout << x->nodes[x->nodes[1] != nullptr]->value << ") ";
    }
    InOrderHijos(x->nodes[0]);
    InOrderHijos(x->nodes[1]);
}

void CBinTree::InOrderHermanos(CBinNode* x)
{
    if (!x) return;
    if (x->nodes[0] && x->nodes[1])
        std::cout << '(' << x->nodes[0]->value << ", " << x->nodes[1]->value << ") ";
    InOrderHermanos(x->nodes[0]);
    InOrderHermanos(x->nodes[1]);
}


void CBinTree::Print()
{
    InOrder(root);
    std::cout << '\n';
}

void CBinTree::Ramas()
{
    InOrderRamas(root);
    std::cout << '\n';
}

void CBinTree::Hojas()
{
    InOrderHojas(root);
    std::cout << '\n';
}

void CBinTree::Hijos()
{
    InOrderHijos(root);
    std::cout << '\n';
}

void CBinTree::Hermanos()
{
    InOrderHermanos(root);
    std::cout << '\n';
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    CBinTree t;
    
    t.Insert(8); t.Insert(4); t.Insert(11); t.Insert(2); t.Insert(6); t.Insert(9); t.Insert(13); t.Insert(1); t.Insert(3); t.Insert(5); t.Insert(7); t.Insert(10); t.Insert(12);
    
    t.Print();
    t.Ramas();
    t.Hojas();
    t.Hijos();
    t.Hermanos();
}

