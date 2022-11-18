#include <iostream>
#include <thread>

void function()
{
    for (int i = 0; i < 1000; i++)
        std::cout << "a";
}

void function2()
{
    for (int i = 0; i < 1000; i++)
        std::cout << "b";
}

int main()
{
    std::thread t1(&function);
    std::thread t2(&function2);
    t2.join();
    t1.join();
    std::string h2;
    return 0;
}