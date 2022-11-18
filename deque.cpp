#include <iostream>

template <typename T>
class Deque
{
    T** map;
    T** beginMap;
    T* beginPage;

    size_t pageSize = 5;
    size_t mapSize = 7;
    size_t size = 0;

    int** calculatePosition(size_t i, int& offset)
    {
        size_t position = beginPage - *(beginMap) + i;
        offset = position % pageSize;
        return beginMap + position / pageSize;
    }
public:

    Deque()
    {
        map = new T*[mapSize];
        for (int i = 0; i < mapSize; i++)
            map[i] = nullptr;
        beginMap = map + mapSize / 2;
        *(beginMap) = new T[pageSize];
        beginPage = *(beginMap) + pageSize / 2;
    }
    void push_back(T v)
    {
        int offset;
        int*& position = *(calculatePosition(size, offset));
        if (!position)
            position = new T[pageSize];
        position[offset] = v;
        size++;
    }
    void push_front(T v)
    {
        
    }
    void pop_back()
    {
        
    }
    void pop_front()
    {

    }
    T& operator[] (size_t i)
    {
        int offset;
        int*& position = *(calculatePosition(i, offset));
        return position[offset];
    }
    void print()
    {
        for (int i = 0; i < size; i++)
            std::cout << operator[](i) << ' ';
        std::cout << '\n';
    }
};

int main()
{
    Deque<int> myList;
    myList.push_back(3);
    myList.push_back(4);
    myList.push_back(5);
    myList.push_back(6);
    myList.push_back(6);
    myList.push_back(6);
    myList.push_back(6);
    myList.print();

    return 0;
}