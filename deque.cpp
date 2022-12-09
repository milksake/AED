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

    T** calculatePosition(int i, int& offset)
    {
        int position = beginPage - *(beginMap) + i;
        offset = position % (int)pageSize;
        if (offset < 0)
        {
            offset += 5;
            return beginMap + (position / (int)pageSize - 1);
        }
        return beginMap + position / (int)pageSize;
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
        T*& page = *(calculatePosition(size, offset));
        if (!page)
            page = new T[pageSize];
        page[offset] = v;
        size++;
    }
    void push_front(T v)
    {
        int offset;
        T** tMap = calculatePosition(-1, offset);
        T*& page = *(tMap);
        if (!page)
        {
            page = new T[pageSize];
            beginMap = tMap;
        }
        beginPage = page + offset;
        page[offset] = v;
        size++;
    }
    void pop_back()
    {
        size--;
    }
    void pop_front()
    {
        int offset;
        T*& page = *(calculatePosition(0, offset));
        if (offset == 4)
            beginMap = map + 1;
        beginPage = *(beginMap) + (offset + 1) % 5;
        size--;
    }
    T& operator[] (int i)
    {
        int offset;
        T*& position = *(calculatePosition(i, offset));
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
    myList.push_back(10);
    myList.push_front(2);
    myList.push_front(2);
    myList.push_front(2);
    myList.push_front(-1);
    myList.pop_back();
    myList.pop_front();
    myList.print();
    std::cout << myList[2];

    return 0;
}