#include <iostream>
#include <stack>
#include <queue>
#include <functional>

#include <utility>

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
    void PrintByLevel();
    void Ramas();
    void Hojas();
    void Hijos();
    void Hermanos();
    void OutlineNodes();
    void InnerNodes();
private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(void (*f)(CBinNode*));
    void InOrder(void (*f)(CBinNode*), CBinNode* x);
    void PreOrder(std::function<void(CBinNode*)> f);
    void PreOrder(std::function<void(CBinNode*)> f, CBinNode* x);
    void PreOrderReverse(std::function<void(CBinNode*)> f);
    void PreOrderReverse(std::function<void(CBinNode*)> f, CBinNode* x);
    void ByLevel(void (*f)(CBinNode*));
    void ByLevel(void (*f)(CBinNode*), CBinNode* x);
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

void CBinTree::InOrder(void (*f)(CBinNode*))
{
    InOrder(f, root);
}

void CBinTree::InOrder(void (*f)(CBinNode*), CBinNode* x)
{
    std::stack<std::pair<CBinNode*, int>> s;
    //first -> node
    //second -> state

    s.push({x, 0});
    
    while (!s.empty())
    {
        switch (s.top().second)
        {
        case 0:
            s.top().second = 1;
            if (s.top().first->nodes[0])
                s.push({s.top().first->nodes[0], 0});
            break;
            
        case 1:
            s.top().second = 2;
            f(s.top().first);
            break;
            
        case 2:
            s.top().second = 3;
            if (s.top().first->nodes[1])
                s.push({s.top().first->nodes[1], 0});
            break;
            
        case 3:
            s.pop();
            break;
        
        default:
            break;
        }
    }


    /*
    struct nodeNstate
    {
        CBinNode* node;
        int state;
        nodeNstate(CBinNode* n = nullptr, int s = 0): node(n), state(s) {}
    };
    
    std::stack<nodeNstate> s;
    s.push(nodeNstate(x));
    while (!s.empty())
    {
        switch (s.top().state)
        {
        case 0:
            s.top().state = 1;
            if (s.top().node->nodes[0])
                s.push(nodeNstate(s.top().node->nodes[0]));
            break;
        case 1:
            s.top().state = 2;
            f(s.top().node);
            break;
        case 2:
            s.top().state = 3;
            if (s.top().node->nodes[1])
                s.push(nodeNstate(s.top().node->nodes[1]));
            break;
        case 3:
            s.pop();
        
        default:
            break;
        }
    }
    */
}

void CBinTree::PreOrder(std::function<void(CBinNode*)> f)
{
    PreOrder(f, root);
}

void CBinTree::PreOrder(std::function<void(CBinNode*)> f, CBinNode* x)
{
    struct nodeNstate
    {
        CBinNode* node;
        int state;
        nodeNstate(CBinNode* n = nullptr, int s = 1): node(n), state(s) {}
    };
    
    std::stack<nodeNstate> s;
    s.push(nodeNstate(x));
    while (!s.empty())
    {
        switch (s.top().state)
        {
        case 0:
            s.top().state = 2;
            if (s.top().node->nodes[0])
                s.push(nodeNstate(s.top().node->nodes[0]));
            break;
        case 1:
            s.top().state = 0;
            f(s.top().node);
            break;
        case 2:
            s.top().state = 3;
            if (s.top().node->nodes[1])
                s.push(nodeNstate(s.top().node->nodes[1]));
            break;
        case 3:
            s.pop();
        
        default:
            break;
        }
    }
}

void CBinTree::PreOrderReverse(std::function<void(CBinNode*)> f)
{
    PreOrderReverse(f, root);
}

void CBinTree::PreOrderReverse(std::function<void(CBinNode*)> f, CBinNode* x)
{
    struct nodeNstate
    {
        CBinNode* node;
        int state;
        nodeNstate(CBinNode* n = nullptr, int s = 1): node(n), state(s) {}
    };
    
    std::stack<nodeNstate> s;
    s.push(nodeNstate(x));
    while (!s.empty())
    {
        switch (s.top().state)
        {
        case 0:
            s.top().state = 3;
            if (s.top().node->nodes[0])
                s.push(nodeNstate(s.top().node->nodes[0]));
            break;
        case 1:
            s.top().state = 2;
            f(s.top().node);
            break;
        case 2:
            s.top().state = 0;
            if (s.top().node->nodes[1])
                s.push(nodeNstate(s.top().node->nodes[1]));
            break;
        case 3:
            s.pop();
        
        default:
            break;
        }
    }
}

void CBinTree::ByLevel(void (*f)(CBinNode*))
{
    ByLevel(f, root);
}

void CBinTree::ByLevel(void (*f)(CBinNode*), CBinNode* x)
{
    std::queue<CBinNode*> q;
    q.push(x);
    for (; !q.empty();)
    {
        f(q.front());
        if (q.front()->nodes[0])
            q.push(q.front()->nodes[0]);
        if (q.front()->nodes[1])
            q.push(q.front()->nodes[1]);
        q.pop();
    }
}

void CBinTree::Print()
{
    InOrder([](CBinNode* n){ std::cout << n->value << ' '; });
}

void CBinTree::PrintByLevel()
{
    ByLevel([](CBinNode* n){ std::cout << n->value << ' '; });
}

void CBinTree::Ramas()
{
    InOrder([](CBinNode* x){
        if (x->nodes[0] || x->nodes[1])
            std::cout << x->value << ' ';
    });
}

void CBinTree::Hojas()
{
    InOrder([](CBinNode* x){
        if (!(x->nodes[0] || x->nodes[1]))
        std::cout << x->value << ' ';
    });
}

void CBinTree::Hijos()
{
    InOrder([](CBinNode* x){
        if (x->nodes[0] || x->nodes[1])
        {
            std::cout << '(' << x->value << ", ";
            if (x->nodes[0] && x->nodes[1])
                std::cout << x->nodes[0]->value << " y " << x->nodes[1]->value << ") ";
            else
                std::cout << x->nodes[x->nodes[1] != nullptr]->value << ") ";
        }
    });
}

void CBinTree::Hermanos()
{
    InOrder([](CBinNode* x){
        if (x->nodes[0] && x->nodes[1])
            std::cout << '(' << x->nodes[0]->value << ", " << x->nodes[1]->value << ") ";
    });
}

void CBinTree::OutlineNodes()
{
    std::cout << root->value << ' ';
    bool print = true;
    PreOrder([&print](CBinNode* x){
        bool hoja = !(x->nodes[0] || x->nodes[1]);
        if (print || hoja)
            std::cout << x->value << ' ';
        if (hoja)
            print = false;
    }, root->nodes[0]);
    std::stack<int> n;
    print = true;
    PreOrderReverse([&print, &n](CBinNode* x){
        bool hoja = !(x->nodes[0] || x->nodes[1]);
        if (print || hoja)
            n.push(x->value);
        if (hoja)
            print = false;
    }, root->nodes[1]);
    while (!n.empty())
    {
        std::cout << n.top() << ' ';
        n.pop();
    }
}

void CBinTree::InnerNodes()
{
    bool print = true;
    PreOrder([&print](CBinNode* x){
        bool hoja = !(x->nodes[0] || x->nodes[1]);
        if (!(print || hoja))
            std::cout << x->value << ' ';
        if (hoja)
            print = false;
    }, root->nodes[0]);
    std::stack<int> n;
    print = true;
    PreOrderReverse([&print, &n](CBinNode* x){
        bool hoja = !(x->nodes[0] || x->nodes[1]);
        if (!(print || hoja))
            n.push(x->value);
        if (hoja)
            print = false;
    }, root->nodes[1]);
    while (!n.empty())
    {
        std::cout << n.top() << ' ';
        n.pop();
    }

    //void (*l)(CBinNode*) = [](CBinNode* x){
    //    if (x->nodes[0] || x->nodes[1])
    //        std::cout << x->value << ' ';
    //};
    //CBinNode* p;
    //for (p = root->nodes[0]; !p->nodes[0]; p = p->nodes[1]);
    //InOrder(l, p->nodes[1]);
    //for (p = root->nodes[1]; !p->nodes[1]; p = p->nodes[0]);
    //InOrder(l, p->nodes[0]);

    //if (root && root->nodes[0] && root->nodes[0]->nodes[1])
    //    InOrder(l, root->nodes[0]->nodes[1]);
    //if (root && root->nodes[1] && root->nodes[1]->nodes[0])
    //    InOrder(l, root->nodes[1]->nodes[0]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    CBinTree t; CBinTree t2;
    
    t.Insert(8); t.Insert(4); t.Insert(11); t.Insert(2); t.Insert(6); t.Insert(9); t.Insert(13); t.Insert(1); t.Insert(3); t.Insert(5); t.Insert(7); t.Insert(10); t.Insert(12);
    t2.Insert(28); t2.Insert(4); t2.Insert(69); t2.Insert(8); t2.Insert(56); t2.Insert(7); t2.Insert(12); t2.Insert(34); t2.Insert(67); t2.Insert(5); t2.Insert(23); t2.Insert(32); t2.Insert(63); t2.Insert(68); t2.Insert(6); t2.Insert(21); t2.Insert(30); t2.Insert(59);

    t.Print(); std::cout << '\n';
    t.Ramas(); std::cout << '\n';
    t.Hojas(); std::cout << '\n';
    t.Hijos(); std::cout << '\n';
    t.Hermanos(); std::cout << '\n';
    t.PrintByLevel(); std::cout << '\n';
    t.OutlineNodes(); std::cout << '\n';
    t.InnerNodes(); std::cout << "\n\n";

    t2.Print(); std::cout << '\n';
    t2.Ramas(); std::cout << '\n';
    t2.Hojas(); std::cout << '\n';
    t2.Hijos(); std::cout << '\n';
    t2.Hermanos(); std::cout << '\n';
    t2.PrintByLevel(); std::cout << '\n';
    t2.OutlineNodes(); std::cout << '\n';
    t2.InnerNodes(); std::cout << '\n';
}
