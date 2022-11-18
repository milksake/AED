#include "vector.cpp"

template <typename T, typename DE>
class Stack
{
private:
    DE de;
public:
    void push(T v)
    {
        de.push_back(v);
    }
    void pop()
    {
        de.pop_back();
    }
    T last()
    {
        return de[de.size - 1];
    }
    bool isEmpty()
    {
        return de.size == 0;
    }
};

int main()
{
    Stack<int, Vector<int>> myStack;
    myStack.push(4);
    myStack.push(12);
    myStack.push(16);
    for (int i = 0; !myStack.isEmpty(); i++)
    {
        std::cout << myStack.last() << ' ';
        myStack.pop();
    }

    return 0;
}
