#include <iostream>

void printMatrix(int (*p)[3])
{
    for (int (*i)[3] = p; i < p + 3; i++)
    {
        for (int *j = *i; j < *i + 3; j++)
        std::cout << *j << ' ';
        std::cout << '\n';
    }
    std::cout << "\n";
}

void mult(int (*p)[3][3])
{
    int (*array1)[3] = p[0];
    int (*array2)[3] = p[1];
    int (*array3)[3] = p[2];
    for (int (*i)[3] = array1, (*x)[3] = array3; i < array1 + 3; i++, x++)
        for (int *b = *array2, *y = *x; b < *array2 + 3; b++, y++)
        {
            int suma = 0;
            for (int *j = *i, *a = b; j < *i + 3; j++, a += 3)
                suma += (*j) * (*a);
            *y = suma;
        }
}

void mult2(int (*p)[3][3])
{
    for (int (*i)[3] = p[0], (*x)[3] = p[2]; i < p[0] + 3; i++, x++)
        for (int *b = *p[1], *y = *x; b < *p[1] + 3; b++, y++)
            for (int *j = *i, *a = b; j < *i + 3; j++, a += 3)
                *y += (*j) * (*a);
}

int main() {
    int A[3][3][3] = {{{1, 3, 5}, {7, 9, 11}, {13, 15, 17}}, {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}};
    printMatrix(A[0]);
    printMatrix(A[1]);
    mult(A);
    printMatrix(A[2]);
    return 0;
}
