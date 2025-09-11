#include <iostream>

int main()
{
    int num;
    std::cin >> num;

    while (num != 0)
    {
        std::cout << num * 2 << std::endl;

        std::cin >> num;
    }
}