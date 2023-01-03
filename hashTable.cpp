#include <iostream>
#include <functional>
#include <list>
#include <vector>
#include <algorithm>

class HashTable
{
private:
    std::function<int(int)> f;
    std::vector<std::list<int>> v;
public:
    HashTable(std::function<int(int)> _f, int _s);
    ~HashTable();
    void insert(int _v);
    void remove(int _v);
    bool find(int _v);
    void print();
};

HashTable::HashTable(std::function<int(int)> _f, int _s) : v(_s), f(_f)
{
}

HashTable::~HashTable()
{
}

void HashTable::insert(int _v)
{
    int pos = f(_v);
    v[pos].push_back(_v);
}

void HashTable::remove(int _v)
{
    int pos = f(_v);
    auto it = std::find(v[pos].begin(), v[pos].end(), _v);
    if (it == v[pos].end())
        return;
    v[pos].erase(it);
}

bool HashTable::find(int _v)
{
    int pos = f(_v);
    auto it = std::find(v[pos].begin(), v[pos].end(), _v);
    return it != v[pos].end();
}

void HashTable::print()
{
    for (auto l : v)
    {
        for (auto x : l)
        {
            std::cout << x << ' ';
        }
        std::cout << '\n';
    }
}


int main()
{
    HashTable h([](int x){ return x % 7; }, 7);
    h.insert(2);
    h.insert(4);
    h.insert(6);
    h.insert(8);
    h.insert(1);
    h.insert(3);
    h.insert(9);
    h.insert(7);
    h.insert(12);
    h.remove(2);
    h.remove(1);
    h.print();
    return 0;
}