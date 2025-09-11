#include <iostream>

int main()
{
	int numElem;
	std::cin >> numElem;

	while (numElem != -1)
	{
		for (int i = 0; i < numElem; i++)
		{
			int dato;
			std::cin >> dato;
			std::cout << dato * 2 << " ";
		}
		std::cout << "\n";

		std::cin >> numElem;
	}
}