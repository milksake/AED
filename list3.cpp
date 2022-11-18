#include <iostream>

template <typename T>
class List3
{
    template <typename U>
    class Node
    {
    public:
        U[3] arr3;
        Node<U>* next = nullptr;
        Node<U>* prev = nullptr;
        Node(U v)
        {
            arr3[0] = v;
        }
    };

    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
public:
    void push_back(T v)
    {
        auto tmp = tail;
        tail = new Node<T>(v);
        tail->prev = tmp;
        if (tmp)
            tmp->next = tail;
        if (!head)
            head = tail;
    }
    void push_front(T v)
    {
        auto tmp = head;
        head = new Node<T>(v);
        head->next = tmp;
        if (tmp)
            tmp->prev = head;
        if (!tail)
            tail = head;
    }
    void pop_back()
    {
        
    }
    void pop_front()
    {

    }
    void print()
    {
        for (Node<T>* p = head; p; p = p->next)
            std::cout << p->value << ' ';
        std::cout << '\n';
        for (Node<T>* p = tail; p; p = p->prev)
            std::cout << p->value << ' ';
        std::cout << '\n';
    }
};

int main()
{
    List3<int> myList;
    myList.push_back(3);
    myList.push_back(4);
    myList.push_back(5);
    myList.push_back(6);
    myList.print();

    return 0;
}