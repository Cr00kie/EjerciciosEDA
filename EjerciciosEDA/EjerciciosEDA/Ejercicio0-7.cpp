#include <iostream>

int main()
{
	int numElem;

	while (std::cin >> numElem)
	{
		for (int i = 0; i < numElem; i++)
		{
			int dato;
			std::cin >> dato;
			std::cout << dato * 2 << " ";
		}
		std::cout << "\n";
	}
}