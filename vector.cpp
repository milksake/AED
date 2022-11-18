#include <iostream>

template <typename T>
class Vector
{
    T* p = nullptr;
public:
    size_t size = 0;
    size_t capacity = 1;
    Vector(size_t c = 5):
        capacity(c)
    {
        p = new T[c];
    }
    void push_back(T value)
    {
        if (++size > capacity)
        {
            capacity *= 2;
            T* newP = new T[capacity];
            for (int i = 0; i < size - 1; i++)
                newP[i] = p[i];
            newP[size - 1] = value;
            delete[] p;
            p = newP;
        }
        else
            p[size - 1] = value;
    }
    void push_front(T value)
    {
        if (++size > capacity)
        {
            capacity *= 2;
            T* newP = new T[capacity];
            *newP = value;
            for (int i = 1; i < size; i++)
                newP[i] = p[i - 1];
            delete[] p;
            p = newP;
        }
        else
        {
            for (int i = size - 1; i > 0; i--)
                p[i] = p[i - 1];
            *p = value;
        }
    }
    void pop_back()
    {
        size--;
    }
    void pop_front()
    {
        size--;
        for (int i = 0; i < size - 1; i++)
        {
            p[i] = p[i + 1];
        }
    }
    void reserve(size_t newC)
    {
        if (newC >= size && newC != capacity)
        {
            capacity = newC;
            T* newP = new T[newC];
            for (int i = 0; i < size; i++)
                    newP[i] = p[i];
            delete[] p;
            p = newP;
        }
    }
    T& operator[](size_t value)
    {
        return *(p + value);
    }
};

void printIntVector(Vector<int> &v)
{
    for (size_t i = 0; i < v.size; i++)
        std::cout << v[i] << ' ';
    std::cout << '\n';
}
/*
int main()
{
    Vector<int> v(7);
    std::cout << v.capacity << ' ' << v.size << '\n';
    printIntVector(v);
    v.push_back(12);
    std::cout << v.capacity << ' ' << v.size << '\n';
    printIntVector(v);
    v.push_back(13);
    v.reserve(1);
    std::cout << v.capacity << ' ' << v.size << '\n';
    printIntVector(v);
    v.push_back(14);
    std::cout << v.capacity << ' ' << v.size << '\n';
    printIntVector(v);
    v.push_back(15);
    std::cout << v.capacity << ' ' << v.size << '\n';
    printIntVector(v);
    
    v.push_front(10);
    std::cout << v.capacity << ' ' << v.size << '\n';
    printIntVector(v);
    v.pop_front();
    std::cout << v.capacity << ' ' << v.size << '\n';
    printIntVector(v);

    return 0;
}*/