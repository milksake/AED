#include <iostream>

template <typename T>
class SList
{
    template <typename U>
    class Node
    {
    public:
        U value;
        Node<U>* next;
        Node(U v, Node<U>* n = nullptr) : value(v), next(n) {}
    };

    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
public:
    bool find(T v, Node<T>**& p)
    {
        for (p = &head; *p && (*p)->value < v; p = &((*p)->next));
        return *p && (*p)->value == v;
    }
    bool insert(T v)
    {
        Node<T>** p;
        if (find(v, p))
            return 0;
        *p = new Node<T>(v, *p);
        return 1;
    }
    bool remove(T v)
    {
        Node<T>** p;
        if (!find(v, p))
            return 0;
        Node<T>* tmp = *p;
        *p = tmp->next;
        delete tmp;
        return 1;
    }
    void print()
    {
        for (Node<T>* p = head; p; p = p->next)
            std::cout << p->value << ' ';
        std::cout << '\n';
    }
};

int main()
{
    SList<int> myList;
    myList.insert(2);
    myList.insert(1);
    myList.insert(4);
    myList.insert(1);
    myList.insert(5);
    myList.insert(6);
    myList.print();
    
    myList.remove(1);
    myList.remove(5);
    myList.print();

    return 0;
}