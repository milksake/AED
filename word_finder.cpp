#include <iostream>
#include <vector>

void printMatrix(char (*matrix)[10])
{
    for (char (*a)[10] = matrix; a < matrix + 10; a++)
    {
        for (char *b = *a; b < *a + 10; b++)
            std::cout << *b << ' ';
        std::cout << '\n';
    }
}

int countWord(const char* str, char (*matrix)[10])
{
    int counter = 0;
    // Find first letter
    std::vector<char*> flp;
    for (char (*a)[10] = matrix; a < matrix + 10; a++)
        for (char *b = *a; b < *a + 10; b++)
            if (*b == *str)
                flp.push_back(b);
    // Check all directions
    if (str[1] == '\0')
        return flp.size();
    for (auto it = flp.begin(); it < flp.end(); it++)
    {
        bool a1 = true, a2 = true, a3 = true, a4 = true;
        for (const char *c = str + 1, *p = *it - 10, *q = *it - 1, *r = *it + 10, *s = *it + 1; *c && (a1 || a2 || a3 || a4); c++, p -= 10, q--, r += 10, s++)
        {
            if (p < *matrix || *p != *c)
                a1 = false;
            if (q < *matrix + ((*it - *matrix) / 10) * 10 || *q != *c)
                a2 = false;
            if (r >= *(matrix + 10) || *r != *c)
                a3 = false;
            if (s >= *matrix + ((*it - *matrix) / 10 + 1) * 10 || *s != *c)
                a4 = false;
        }
        counter += a1 + a2 + a3 + a4;
    }
    return counter;
}

int countWord2(const char* str, char (*matrix)[10])
{
    int counter = 0;
    bool oneCharacter = false;
    if (str[1] == '\0')
        oneCharacter = true;
    // Find first letter
    for (char (*a)[10] = matrix; a < matrix + 10; a++)
        for (char *b = *a; b < *a + 10; b++)
            if (*b == *str)
            {
                if (oneCharacter)
                    counter++;
                else
                {
                    // Check all directions
                    bool a1 = true, a2 = true, a3 = true, a4 = true;
                    for (const char *c = str + 1, *p = b - 10, *q = b - 1, *r = b + 10, *s = b + 1; *c && (a1 || a2 || a3 || a4); c++, p -= 10, q--, r += 10, s++)
                    {
                        if (p < *matrix || *p != *c)
                            a1 = false;
                        if (q < *matrix + ((b - *matrix) / 10) * 10 || *q != *c)
                            a2 = false;
                        if (r >= *(matrix + 10) || *r != *c)
                            a3 = false;
                        if (s >= *matrix + ((b - *matrix) / 10 + 1) * 10 || *s != *c)
                            a4 = false;
                    }
                    counter += a1 + a2 + a3 + a4;
                }
            }
    return counter;
}

int main()
{
    char m[10][10] =
    {
        {'P', 'A', 'L', 'T', 'A', 'K', 'S', 'U', 'Q', 'D'},
        {'A', 'I', 'D', 'L', 'Q', 'I', 'E', 'R', 'T', 'H'},
        {'L', 'S', 'T', 'Y', 'R', 'E', 'S', 'K', 'I', 'G'},
        {'T', 'Q', 'Y', '/', 'O', 'K', 'V', 'M', 'H', 'L'},
        {'A', 'T', 'L', 'A', 'P', 'A', 'T', 'Q', 'M', 'X'},
        {'P', 'A', 'L', 'T', 'A', 'K', 'S', 'U', 'Q', 'D'},
        {'A', 'I', 'D', 'L', 'L', 'I', 'E', 'R', 'T', 'H'},
        {'J', 'S', 'T', 'Y', 'T', 'E', 'S', 'P', 'A', 'L'},
        {'T', 'A', 'P', 'P', 'O', 'K', 'V', 'M', 'H', 'L'},
        {'A', 'T', 'L', 'A', 'P', 'A', 'T', 'Q', 'M', 'X'},
    };
    printMatrix(m);
    std::cout << countWord2("PALTA", m) << '\n';
    return 0;
}