#include <iostream>
#include <time.h>
#include <chrono>
#include <fstream>
#include <thread>
#include <cmath>

class ComparisonPolymorphism
{
public:
    virtual bool compare(int a, int b) = 0;
};

class LessPolymorphism:
    public ComparisonPolymorphism
{
public:
    inline bool compare(int a, int b) override
    {
        return a < b;
    }
};

class GreaterPolymorphism:
    public ComparisonPolymorphism
{
public:
    inline bool compare(int a, int b) override
    {
        return a > b;
    }
};

class LessFunctionObject
{
public:
    bool operator()(int a, int b)
    {
        return a < b;
    }
};

class GreaterFunctionObject
{
public:
    bool operator()(int a, int b)
    {
        return a > b;
    }
};

void printArray(int *a, int n)
{
    for (int *p = a; p < a + n; p++)
        std::cout << *p << ' ';
    std::cout << '\n';
}

void generateArray(int *a, int n)
{
    for (int *p = a; p < a + n; p++)
        *p = rand() % 100;
}

void copyArray(int *a, int n, int *b)
{
    for (int i = 0; i < n; i++)
        b[i] = a[i];
}

void quicksortLess(int *a, int n)
{
    int* pivot = a;
    int* p = a + n - 1;
    while (pivot != p)
    {
        for (; p != pivot; p--)
        {
            if (*pivot < *p)
            {
                std::swap(*pivot, *p);
                std::swap(pivot, p);
                break;
            }
        }
        for (; p != pivot; p++)
        {
            if (!(*pivot < *p))
            {
                std::swap(*pivot, *p);
                std::swap(pivot, p);
                break;
            }
        }
    }
    if (pivot > a + 1)
        quicksortLess(a, pivot - a);
    if (pivot < a + n - 2)
        quicksortLess(pivot + 1, a + n - pivot - 1);
}

void quicksortGreater(int *a, int n)
{
    int* pivot = a;
    int* p = a + n - 1;
    while (pivot != p)
    {
        for (; p != pivot; p--)
        {
            if (*pivot > *p)
            {
                std::swap(*pivot, *p);
                std::swap(pivot, p);
                break;
            }
        }
        for (; p != pivot; p++)
        {
            if (!(*pivot > *p))
            {
                std::swap(*pivot, *p);
                std::swap(pivot, p);
                break;
            }
        }
    }
    if (pivot > a + 1)
        quicksortGreater(a, pivot - a);
    if (pivot < a + n - 2)
        quicksortGreater(pivot + 1, a + n - pivot - 1);
}

void quicksortPolimorphism(int *a, int n, ComparisonPolymorphism* compare)
{
    int* pivot = a;
    int* p = a + n - 1;
    while (pivot != p)
    {
        for (; p != pivot; p--)
        {
            if (compare->compare(*pivot, *p))
            {
                std::swap(*pivot, *p);
                std::swap(pivot, p);
                break;
            }
        }
        for (; p != pivot; p++)
        {
            if (!compare->compare(*pivot, *p))
            {
                std::swap(*pivot, *p);
                std::swap(pivot, p);
                break;
            }
        }
    }
    if (pivot > a + 1)
        quicksortPolimorphism(a, pivot - a, compare);
    if (pivot < a + n - 2)
        quicksortPolimorphism(pivot + 1, a + n - pivot - 1, compare);
}

template <typename T>
void quicksortFunctionObject(int *a, int n, T compare)
{
    int* pivot = a;
    int* p = a + n - 1;
    while (pivot != p)
    {
        for (; p != pivot; p--)
        {
            if (compare(*pivot, *p))
            {
                std::swap(*pivot, *p);
                std::swap(pivot, p);
                break;
            }
        }
        for (; p != pivot; p++)
        {
            if (!compare(*pivot, *p))
            {
                std::swap(*pivot, *p);
                std::swap(pivot, p);
                break;
            }
        }
    }
    if (pivot > a + 1)
        quicksortFunctionObject(a, pivot - a, compare);
    if (pivot < a + n - 2)
        quicksortFunctionObject(pivot + 1, a + n - pivot - 1, compare);
}

void quicksortFunctionPointer(int *a, int n, bool (*compare)(int, int))
{
    int* pivot = a;
    int* p = a + n - 1;
    while (pivot != p)
    {
        for (; p != pivot; p--)
        {
            if (compare(*pivot, *p))
            {
                std::swap(*pivot, *p);
                std::swap(pivot, p);
                break;
            }
        }
        for (; p != pivot; p++)
        {
            if (!compare(*pivot, *p))
            {
                std::swap(*pivot, *p);
                std::swap(pivot, p);
                break;
            }
        }
    }
    if (pivot > a + 1)
        quicksortFunctionObject(a, pivot - a, compare);
    if (pivot < a + n - 2)
        quicksortFunctionObject(pivot + 1, a + n - pivot - 1, compare);
}

bool less(int a, int b)
{
    return a < b;
}

bool greater(int a, int b)
{
    return a > b;
}

// Merge two lists using function pointer
void mergeSortedArrays(int *a, int sizeA, int sizeB, bool (*comparison)(int, int))
{
    auto calculate_gap = [](int n) {return (n == 1) ? 0 : n / 2 + n % 2;};
    size_t gap = calculate_gap(sizeA + sizeB);
    for (;gap != 0; gap = calculate_gap(gap))
        for (int *p = a; p + gap < a + sizeA + sizeB; p++)
            if (comparison(*p, *(p + gap)))
                std::swap(*p, *(p + gap));
}

// Threads(???) using function pointer
void thread_sort(int *a, int n, bool (*comparison)(int, int))
{
    auto numThr = std::thread::hardware_concurrency();
    std::thread** arrayThr = new std::thread*[numThr];
    size_t size = n / numThr;
    size_t i = 0;
    for (; i < numThr - 1; i++)
        arrayThr[i] = new std::thread(&quicksortFunctionPointer, a + i * size, size, comparison);
    arrayThr[i] = new std::thread(&quicksortFunctionPointer, a + i * size, n - size * i, comparison);
    for (int j = 0; j < numThr; j++)
    {
        arrayThr[j]->join();
        delete arrayThr[j];
    }
    for (size_t groups = numThr / 2; groups != 1; groups /= 2, size *= 2)
    {
        for (i = 0; i < groups - 1; i++)
            arrayThr[i] = new std::thread(&mergeSortedArrays, a + 2 * i * size, size, size, comparison);
        arrayThr[i] = new std::thread(&mergeSortedArrays, a + 2 * i * size, size, n - (2 * i + 1) * size, comparison);
        for (int j = 0; j < groups; j++)
        {
            arrayThr[j]->join();
            delete arrayThr[j];
        }
    }
    delete[] arrayThr;
    mergeSortedArrays(a, size, size, comparison);
}

void orderArrayAllMethods(int n, bool comparison = false)
{
    int* array = new int[n];
    int* arrayCopy = new int[n];
    int* arrayCopy2 = new int[n];
    int* arrayCopy3 = new int[n];
    int* arrayCopy4 = new int[n];
    generateArray(array, n);
    copyArray(array, n, arrayCopy);
    copyArray(array, n, arrayCopy2);
    copyArray(array, n, arrayCopy3);
    copyArray(array, n, arrayCopy4);
    std::ofstream file;
    file.open("data.csv", std::fstream::app);
    file << n;
    if (comparison)
    {
        auto start = std::chrono::steady_clock::now();
        quicksortLess(arrayCopy3, n);
        auto end = std::chrono::steady_clock::now();
        file << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        LessPolymorphism comparePolymorphism;
        start = std::chrono::steady_clock::now();
        quicksortPolimorphism(array, n, &comparePolymorphism);
        end = std::chrono::steady_clock::now();
        file << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        LessFunctionObject compareFunctionObject;
        start = std::chrono::steady_clock::now();
        quicksortFunctionObject(arrayCopy, n, compareFunctionObject);
        end = std::chrono::steady_clock::now();
        file << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = std::chrono::steady_clock::now();
        quicksortFunctionPointer(arrayCopy2, n, &less);
        end = std::chrono::steady_clock::now();
        file << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = std::chrono::steady_clock::now();
        thread_sort(arrayCopy4, n, &less);
        end = std::chrono::steady_clock::now();
        file << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    else
    {
        auto start = std::chrono::steady_clock::now();
        quicksortGreater(arrayCopy3, n);
        auto end = std::chrono::steady_clock::now();
        file << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        GreaterPolymorphism comparePolymorphism;
        start = std::chrono::steady_clock::now();
        quicksortPolimorphism(array, n, &comparePolymorphism);
        end = std::chrono::steady_clock::now();
        file << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        GreaterFunctionObject compareFunctionObject;
        start = std::chrono::steady_clock::now();
        quicksortFunctionObject(arrayCopy, n, compareFunctionObject);
        end = std::chrono::steady_clock::now();
        file << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = std::chrono::steady_clock::now();
        quicksortFunctionPointer(arrayCopy2, n, &greater);
        end = std::chrono::steady_clock::now();
        file << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        start = std::chrono::steady_clock::now();
        thread_sort(arrayCopy4, n, &less);
        end = std::chrono::steady_clock::now();
        file << ',' << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    file << '\n';
    file.close();
    delete[] array;
    delete[] arrayCopy;
    delete[] arrayCopy2;
    delete[] arrayCopy3;
}

void printOrderedArray(int n, bool comparison = false)
{
    int* array = new int[n];
    int* arrayCopy = new int[n];
    int* arrayCopy2 = new int[n];
    int* arrayCopy3 = new int[n];
    int* arrayCopy4 = new int[n];
    generateArray(array, n);
    copyArray(array, n, arrayCopy);
    copyArray(array, n, arrayCopy2);
    copyArray(array, n, arrayCopy3);
    copyArray(array, n, arrayCopy4);
    if (comparison)
    {
        std::cout << "Normal Function\n";
        printArray(arrayCopy3, n);
        quicksortLess(arrayCopy3, n);
        printArray(arrayCopy3, n);
        std::cout << "Using Polymorphism\n";
        printArray(array, n);
        LessPolymorphism comparePolymorphism;
        quicksortPolimorphism(array, n, &comparePolymorphism);
        printArray(array, n);
        std::cout << "Using Function Objects\n";
        printArray(arrayCopy, n);
        LessFunctionObject compareFunctionObject;
        quicksortFunctionObject(arrayCopy, n, compareFunctionObject);
        printArray(arrayCopy, n);
        std::cout << "Using a Function Pointer\n";
        printArray(arrayCopy2, n);
        quicksortFunctionPointer(arrayCopy2, n, &less);
        printArray(arrayCopy2, n);
        std::cout << "Using Threads with a Function Pointer\n";
        printArray(arrayCopy4, n);
        thread_sort(arrayCopy4, n, &less);
        printArray(arrayCopy4, n);
    }
    else
    {
        std::cout << "Normal Function\n";
        printArray(arrayCopy3, n);
        quicksortGreater(arrayCopy3, n);
        printArray(arrayCopy3, n);
        std::cout << "Using Polymorphism\n";
        printArray(array, n);
        GreaterPolymorphism comparePolymorphism;
        quicksortPolimorphism(array, n, &comparePolymorphism);
        printArray(array, n);
        std::cout << "Using Function Objects\n";
        printArray(arrayCopy, n);
        GreaterFunctionObject compareFunctionObject;
        quicksortFunctionObject(arrayCopy, n, compareFunctionObject);
        printArray(arrayCopy, n);
        std::cout << "Using a Function Pointer\n";
        printArray(arrayCopy2, n);
        quicksortFunctionPointer(arrayCopy2, n, &greater);
        printArray(arrayCopy2, n);
        std::cout << "Using Threads with a Function Pointer\n";
        printArray(arrayCopy4, n);
        thread_sort(arrayCopy4, n, &greater);
        printArray(arrayCopy4, n);
    }
    std::cout << '\n';
    delete[] array;
    delete[] arrayCopy;
    delete[] arrayCopy2;
    delete[] arrayCopy3;
    delete[] arrayCopy4;
}

int main()
{
    srand(time(NULL));
    std::ofstream file;
    file.open("data.csv");
    file << "n,Normal,Polymorphism,Function Object,Function Pointer,Threads (FP)\n";
    file.close();
    for (int i = 1000; i <= 100000; i += 1000)
    {
        orderArrayAllMethods(i, false);
    }
    //printOrderedArray(25);
    //printOrderedArray(25, true);
    return 0;
}