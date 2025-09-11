#include <iostream>

int main()
{
    int numDup;
    std::cin >> numDup;

    while (numDup-- > 0)
    {
        int num;
        std::cin >> num;

        std::cout << num * 2 << std::endl;
    }
}
