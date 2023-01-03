#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

class sparseMatrix
{
private:
    struct sparseNode
    {
        size_t x;
        size_t y;
        int v;
    };    

    std::vector<std::list<sparseNode>> matrix[2];
public:
    sparseMatrix(size_t r, size_t c);
    ~sparseMatrix();
    void set(size_t r, size_t c, int v);
    void get(size_t r, size_t c, int v);
};

sparseMatrix::sparseMatrix(size_t r, size_t c) : matrix {std::vector<std::list<sparseNode>>(r), std::vector<std::list<sparseNode>>(c)}
{
}

sparseMatrix::~sparseMatrix()
{
}

void sparseMatrix::set(size_t r, size_t c, int v)
{
    auto it = matrix[0][r].begin();
    for (; it != matrix[0][r].end() && it->y < c; it++);
    if (it == matrix[0][r].end()) // insert
    {
        return;
    }
    if (it->y == c)
    {
        //set or delete
        if (v != 0)
        {
            return;
        }
        it->v = v;
        return;
    }
    //insert

}

void sparseMatrix::get(size_t r, size_t c, int v)
{

}

int main()
{
    sparseMatrix m(2, 2);
    return 0;
}
